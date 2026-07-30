#include "Game.h"
#include <cstdio>

Game::Game(){

    scene = START;

    sudokuBtn = {260, 180, 300, 60};
    killersudokuBtn = {260, 260, 300, 60};
    largesudokuBtn = {260, 340, 300, 60};
    killerlargeBtn = {260, 420, 300, 60};
    exitBtn  = {260, 500, 300, 60};

    my_name[0] = '\0';
    nameLength = 0;

    jpFont = LoadFontEx("assets/font/MPLUSRounded1c-Regular.ttf", 40, nullptr, 0);
}

Game::~Game(){

    UnloadFont(jpFont);

}

void Game::Update(){

    switch(scene){

    case START:

        if(CheckCollisionPointRec(GetMousePosition(), sudokuBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            sudoku.SetSudokuFlag(0);
            scene = MENU;
        }

        if(CheckCollisionPointRec(GetMousePosition(), killersudokuBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            sudoku.SetSudokuFlag(1);
            scene = MENU;
        }

        if(CheckCollisionPointRec(GetMousePosition(), largesudokuBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            sudoku.SetSudokuFlag(2);
            scene = MENU;
        }

        if(CheckCollisionPointRec(GetMousePosition(), killerlargeBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            sudoku.SetSudokuFlag(3);
            scene = MENU;
        }

        if(CheckCollisionPointRec(GetMousePosition(), exitBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
            CloseWindow();
        }

        break;

    case MENU:

        menu.Update();

        if(menu.GetDifficulty() != -1 && menu.GetDifficulty() != 2){
            sudoku.SetDifficulty(menu.GetDifficulty());
            scene = NAME;
        }

        if(menu.GetDifficulty() == 2){
            scene = START;
        }

        break;

    case NAME:

        name.Update(my_name, nameLength);

        if(name.GetDifficulty() == 0){
            scene = MENU;
        }

        if(name.GetDifficulty() == 2){
            sudoku.StartGame();
            scene = SUDOKU;
        }

        break;
    
    case SUDOKU:

        sudoku.Update(my_name, nameLength);

        if(sudoku.GetDifficulty() == 0){
            name.Reset(my_name, nameLength);
            sudoku.ResetBoard();
            sudoku.ResetTimer();
            result.Reset();
            scene = START;
        }

        if(sudoku.GetDifficulty() == 2){
            result.SetResult(my_name, sudoku.GetDifficultyMode(), sudoku.GetElapsedTime());
            SetWindowSize(800, 600);
            scene = RESULT;
        }

        break;

    case RESULT:

        result.Update();

        if(result.GetDifficulty() == 0){
            sudoku.StartGame();
            scene = SUDOKU;
        }

        if(result.GetDifficulty() == 1){
            name.Reset(my_name, nameLength);
            result.Reset();
            scene = START;
        }

        break;
    }
}

void Game::Draw(){

    switch(scene){

    case START:

        DrawTextEx(jpFont, "GAME SELECT", {300, 80}, 40, 2, WHITE);

        DrawRectangleRec(sudokuBtn, SKYBLUE);
        DrawTextEx(jpFont, "SUDOKU", {360, 195}, 30, 2, BLACK);

        DrawRectangleRec(killersudokuBtn, ORANGE);
        DrawTextEx(jpFont, "KILLER SUDOKU", {320, 275}, 30, 2, BLACK);

        DrawRectangleRec(largesudokuBtn, PURPLE);
        DrawTextEx(jpFont, "LARGE SUDOKU", {330, 355}, 30, 2, BLACK);

        DrawRectangleRec(killerlargeBtn, PINK);
        DrawTextEx(jpFont, "KILLER LARGE SUDOKU", {275, 435}, 30, 2, BLACK);

        DrawRectangleRec(exitBtn, RED);
        DrawTextEx(jpFont, "EXIT", {380, 515}, 30, 2, BLACK);

        break;

    case MENU:

        menu.Draw(jpFont);

        break;

    case NAME:

        name.Draw(jpFont);

        break;
    case SUDOKU:

        sudoku.Draw(jpFont, menu.GetDifficulty(), my_name);

        break;
    
    case RESULT:

        result.Draw(jpFont);

        break;
    }
}