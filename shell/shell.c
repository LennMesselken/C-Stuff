#include <stdio.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define TOKEN_DELIMITER " "

void shell_interactive(void);
void shell_no_interactive(void);
char* read_next_line(void);
char** tokenize(char* line);
int execute_command(char** args);


int main (void){
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
    int status = -1;
    line = read_next_line();
    args = tokenize(line);
    printf("%s", args[0]);
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

char** tokenize(char* line){
    int bufsize = 64;
    int i = 0;
    char** tokens = malloc(bufsize * sizeof(char*));
    char* token;

    if(!tokens){
        fprintf(stderr, "Allocation Error in Tokenizing Input");
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
    char* built_in_funcs_list[] = {"cd", "ls", "echo", "exit"};
    int (*built_in_funcs[])(char **) = {&own_cd, & own_ls, &own_echo, &own_exit};

    if (args[0] == NULL) {
        return -1;
    }

    for (int i = 0; i < sizeof(built_in_funcs) / sizeof(char*); i++){
        if (strcmp(args[0], built_in_funcs_list[i]) == 0){
            return ((*built_in_funcs[i])(args));
        }
    }
    return new_process(args);
}




int own_cd (char** args){

}

int own_ls (char** args){
    
}

int own_echo (char** args){
    
}

int own_exit (char** args){
    
}