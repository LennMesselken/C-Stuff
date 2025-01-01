#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Functions Definitions

void add_todo(char* file, char* task);
void get_todo(char* file, char* task);
void list_todos(char* file);
void complete_todo(char* file, char* task);

int main(int argc,char* argv[]){
    if (argc > 3 && strcmp(argv[1], "-a") == 0){
        add_todo(argv[2], argv[3]);
    } else if (argc > 3 && strcmp(argv[1], "-g") == 0){
        get_todo(argv[2], argv[3]);
    } else if (argc > 2 && strcmp(argv[1], "-l") == 0){
        list_todos(argv[2]);
    } else if (argc > 3 && strcmp(argv[1], "-c") == 0){
        complete_todo(argv[2], argv[3]);
    }


    return 0;
}

//Adding new todo to parsed file

void add_todo(char* file, char* task){
    FILE* fptr;
    fptr = fopen(file,"a"); //Opens passed file
    //fprintf(fptr, "%d ", current_id); //Writes current id of task infront of task to file
    fprintf(fptr, "%s\n", task); //Writes passed task to file
    fclose(fptr);
//    current_id++;
    
}

//Printing todo to command line if found in parsed file

void get_todo(char* file, char* task){
    FILE* fptr;
    char line[1024]; 
    fptr = fopen(file, "r");
    while(fgets(line, 100, fptr)){
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, task) == 0){
            printf("%s\n", line);
            break;
        } 
    }
    fclose(fptr);

}

//List all todos in parsed file

void list_todos(char* file){
    FILE* fptr;
    fptr = fopen(file, "r");
    char line[1024];
    while(fgets(line, sizeof(line), fptr)){
        printf("%s", line);
    }
    fclose(fptr);
}

//Remove specified todo in parsed file

void complete_todo(char* file, char* task){
    FILE* fptr;
    fptr = fopen(file, "r");
    FILE* fptr_temp = fopen("temp.txt", "a");
    char line[1024];
    while(fgets(line, sizeof(line), fptr)){
        line[strcspn(line, "\n")] = '\0';
        if (strcmp(line, task) != 0){
           fprintf(fptr_temp,"%s\n", line);
        }  
    }
    fclose(fptr);
    fclose(fptr_temp);
    remove(file);
    rename("temp.txt", file);
}