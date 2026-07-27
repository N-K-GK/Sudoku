#pragma once
#include "raylib.h"
#include "Menu.h"
#include "Name.h"
#include "Sudoku.h"
#include "Result.h"

class Game{
private:

    enum Scene{
        START,
        MENU,
        NAME,
        SUDOKU,
        RESULT
    };

    Scene scene;

    Rectangle sudokuBtn;
    Rectangle killersudokuBtn;
    Rectangle largesudokuBtn;
    Rectangle exitBtn;

    Font jpFont;

    Menu menu;
    Name name;
    Sudoku sudoku;
    Result result;

    char my_name[100];
    int nameLength;

public:

    Game();
    ~Game();

    void Update();
    void Draw();
};