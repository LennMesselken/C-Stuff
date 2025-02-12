#include "include/raylib.h"
#include <stdio.h>

int main() {
    InitWindow(800, 600, "Hello Raylib");
    while (!WindowShouldClose()) {
        SetWindowPosition(0,0);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        DrawText("This is a test", 350, 280, 20, BLACK);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}