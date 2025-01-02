#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN_DELIMITER " \n\t"

void shell_interactive(void);
void shell_no_interactive(void);
char* read_next_line(void);
char* read_stream(void);
char** tokenize(char* line);
int execute_command(char** args);
int new_process(char** args);

int own_cd(char** args);
int own_echo(char** args);
int own_exit(char** args);


int main (void){
    //Check if Running in Terminal
    if (isatty(STDIN_FILENO) == 1){
        shell_interactive();
    } else {
//        shell_no_interactive();
    }
    return 0;
}

void shell_interactive(void){
    char* line;
    char **args;
    int status = 0;
    do {
        line = read_next_line();
        args = tokenize(line);
        status = execute_command(args);
        //Avoid Memory Leaks
        //free(line);
        //free(args);
        //Check if Process should be exited
        if (status != 0){
            exit(status);
        }
    } while (0);
}

void shell_no_interactive(void){
    char* line;
    char **args;
    int status =  0;
    do {
        line = read_stream();
        args = tokenize(line);
        status = execute_command(args);
        //Avoid Memory Leaks
        free(line);
        free(args);
        //Check if Process should be exited
        if (status != 0){
            exit(status);
        }
    } while (0);
}

char* read_next_line(void){
    static char result [1024];
    char c;
    int i = 0;
    while ((c = getchar()) != EOF){
        result[i++] = c;
    }
    return result;
}

char* read_stream(void){
    int bufsize = 1024;
    int i = 0;
    char* line = malloc(bufsize * sizeof(char));
    int character;
    if (line == NULL){
        fprintf(stderr, "allocation error in read_stream");
        exit(EXIT_FAILURE);
    }
    while (1){
        character = getchar();
        //Check if EOF is reached
        if (character == EOF){
            free(line);
            exit(EXIT_SUCCESS);
        } else if (character == '\n'){
            line[i] = '\0';
            return (line);
        } else {
            line[i++] = character;
        }


    }

}

char** tokenize(char* line){
    int bufsize = 64;
    int i = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if(!tokens){
        fprintf(stderr, "Allocation Error in Tokenizing Input");
        exit(EXIT_FAILURE);
    }
    token = strtok(line, TOKEN_DELIMITER);
    while (token != NULL){
        if (token[0] == '#'){
            break;
        }
        tokens[i++] = token;
        token = strtok(NULL, TOKEN_DELIMITER);
    }
    
    return tokens;

}

int execute_command (char** args){
    char* built_in_funcs_list[] = {"cd", "echo", "exit"};
    int (*built_in_funcs[])(char **) = {&own_cd, &own_echo, &own_exit};
    //Check if No Command was entered
    if (args[0] == NULL) {
        return -1;
    }
    //Check if Command is a built in function
    for (int i = 0; i < sizeof(built_in_funcs) / sizeof(char*); i++){
        if (strcmp(args[0], built_in_funcs_list[i]) == 0){
            return ((*built_in_funcs[i])(args));
        }
    }
    //If Command is unknown create new process 
    return (new_process(args));
}

//Create mew Process to Execute Unknown Command by Searching the Executable File
int new_process(char** args){
    //pid_t is a structure containing info for the child process
    pid_t pid;
    int status;
    //create a child process
    pid = fork();
    if (pid == 0){
        //execvp finds executable name (args[0]) ; p means os finds path to file
        if(execvp(args[0], args) == -1){
            perror("error in new process: child process");
            exit(EXIT_FAILURE);
        }
       
    } else if (pid < 0){
        perror("error in new process: forking");
    } else {
        //parent process waits for child process' status to change
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }
    return (-1);
}

int own_cd (char** args){
    if (args[1] == NULL){
        perror("error in own_cd: no path specified");
        exit(EXIT_FAILURE);
    }
    return (chdir(args[1]));
}

int own_echo (char** args){
    if (args[1] == NULL){
        perror("error in own_echo: nothing to echo");
        exit(EXIT_FAILURE);
    }
    int i = 1;
    while(args[i] != NULL){
        printf("%s ", args[i]);
        i++;
    }
    printf("\n");
    return 0;
}

int own_exit (char** args){
    printf("\n");
    return 0;
} 