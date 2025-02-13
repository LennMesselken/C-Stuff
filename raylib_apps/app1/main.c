#include "include/raylib.h"
#include <stdio.h>
#include <stdlib.h>

#define X_SIZE 800
#define Y_SIZE 600

int main() {
    InitWindow(X_SIZE, Y_SIZE, "Hello World");
    SetTargetFPS(120);
    while (!WindowShouldClose()) {
        
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a test", 350, 280, 20, BLACK);
        DrawFPS(0,0);
        EndDrawing();

        
    }
    CloseWindow();
    return 0;
}