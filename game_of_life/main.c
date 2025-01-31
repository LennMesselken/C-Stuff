#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

#define Y_SIZE 10
#define X_SIZE 100

#define MAX_GENERATIONS 20

const char DEAD_CHAR = ' ';
const char ALIVE_CHAR = '#';
const double SLEEP_TIME = 2;

char game_matrix[Y_SIZE][X_SIZE];
char neighbor_matrix[Y_SIZE][X_SIZE];

int generation = 0;

typedef struct{
    int x;
    int y;
} Cell;

void initialise_board(){
    for (int i = 0; i < Y_SIZE; i++){
        for (int j = 0; j < X_SIZE; j++){
            game_matrix[i][j] = DEAD_CHAR;
        }
    }

    game_matrix[5][5] = ALIVE_CHAR;
    game_matrix[4][5] = ALIVE_CHAR;
    game_matrix[6][5] = ALIVE_CHAR;
    game_matrix[6][4] = ALIVE_CHAR;
    game_matrix[5][3] = ALIVE_CHAR;
}

void print_board(){
    printf("Current Board (Gen %d): \n", generation);
    for (int i = 0; i < Y_SIZE; i++){
        for (int j = 0; j < X_SIZE; j++){
            printf("%c", game_matrix[i][j]);
        }
        printf("\n");
    }
}
int check_coords(int y, int x){
    if (x > 0 && y > 0 && x < X_SIZE && y < Y_SIZE){
        return 1;
    } else {
        return 0;
    }
}
int count_neighbor(int y, int x){
    int neighbors = 0;
    //Check if coords are not on the outer most loop
    if (check_coords(y, x) == 0){
        return 0;
    }
    //Above
    if (game_matrix[y-1][x] == ALIVE_CHAR){neighbors++;} 

    //Below
    if (game_matrix[y+1][x] == ALIVE_CHAR){neighbors++;} 

    //Left
    if (game_matrix[y][x-1] == ALIVE_CHAR){neighbors++;} 

    //Right
    if (game_matrix[y][x+1] == ALIVE_CHAR){neighbors++;} 

    //Above Left
    if (game_matrix[y-1][x-1] == ALIVE_CHAR){neighbors++;} 

    //Above Right
    if (game_matrix[y-1][x+1] == ALIVE_CHAR){neighbors++;} 

    //Below Left
    if (game_matrix[y+1][x-1] == ALIVE_CHAR){neighbors++;} 

    //Below Right
    if (game_matrix[y+1][x+1] == ALIVE_CHAR){neighbors++;} 

    return neighbors;
}

int dead_or_alive(char current_state, int neighbors){
    if (neighbors < 2 || neighbors > 3){
        return 0;
    } else if ((neighbors == 2 || neighbors  == 3) && current_state == '#'){
        return 1;
    } else if (neighbors == 3 && current_state == ' '){
        return 1;
    } else {
        return 0;
    }
}
void update_game_matrix(){
    for (int i = 0; i < Y_SIZE; i++){
        for (int j = 0; j < X_SIZE; j++){
            char current_state = game_matrix[i][j];
            int neighbors = neighbor_matrix[i][j];
            game_matrix[i][j] = dead_or_alive(current_state, neighbors) == 1 ? ALIVE_CHAR : DEAD_CHAR;
        }
    }
}

void update_neighbor_matrix(){
    for (int i = 0; i < Y_SIZE; i++){
        for (int j = 0; j < X_SIZE; j++){
            neighbor_matrix[i][j] = count_neighbor(i,j);
        }
    }
}
void game_loop(){
    print_board();
    update_neighbor_matrix();
    update_game_matrix();
    generation++;
}



int main(){
    initialise_board();
    for (int i = 0; i < MAX_GENERATIONS; i++){
        game_loop();
        sleep(1);
    }

}

