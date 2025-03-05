#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>
#include "include/bst.h"

#define X_SIZE 800
#define Y_SIZE 600

#define MATRIX_X_SIZE 16
#define MATRIX_Y_SIZE 8
#define MATRIX_ELEMENT_SIZE 32
#define MATRIX_PADDING 8
#define TEXT_LENGTH 4

int main() {
    BST test_bst;
    BST_init(&test_bst);
    InitWindow(X_SIZE, Y_SIZE, "Hello World");
    SetTargetFPS(120);

    char* test_matrix[MATRIX_Y_SIZE][MATRIX_X_SIZE];
    for (int i = 0; i < MATRIX_Y_SIZE; i++) {
        for (int j = 0; j < MATRIX_X_SIZE; j++) {
            test_matrix[i][j] = ""; // Empty at start
        }
    }
    test_matrix[0][0] = "1_";
    test_matrix[0][1] = "2_";
    test_matrix[0][2] = "3_";

    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for(int i = 0; i < MATRIX_Y_SIZE; i++){
            for(int j = 0; j < MATRIX_X_SIZE; j++){
                int x_Pos = 32 + (j * (MATRIX_ELEMENT_SIZE + MATRIX_PADDING));
                int y_Pos = 32 + (i * (MATRIX_ELEMENT_SIZE + MATRIX_PADDING));
                DrawRectangle(x_Pos, y_Pos, MATRIX_ELEMENT_SIZE, MATRIX_ELEMENT_SIZE, BLACK);
                DrawText(test_matrix[i][j], x_Pos + 4, y_Pos + 2 , 12, RAYWHITE);
            }
        }
        DrawFPS(0,0);
          
        EndDrawing();

        
    }
    CloseWindow();
    return 0;
}