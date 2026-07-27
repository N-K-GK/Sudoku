#include "raylib.h"
#include "Game.h"
#include "Sudoku.h"
#include <random>

int main(){
    srand(time(NULL));
    
    InitWindow(800, 600, "Sudoku");

    SetTargetFPS(60);

    Game game;

    while(!WindowShouldClose()){

        game.Update();

        BeginDrawing();

        ClearBackground(DARKGREEN);

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}