#include "Menu.h"

Menu::Menu(){

    normalBtn = {260, 180, 300, 60};
    hardBtn = {260, 300, 300, 60};
    veryhardBtn = {260, 420, 300, 60};
    exitBtn = {680, 10, 80, 60};

    difficulty = -1;
}

void Menu::Update(){

    difficulty = -1;

    if(CheckCollisionPointRec(GetMousePosition(), normalBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 0;
    }

    if(CheckCollisionPointRec(GetMousePosition(), hardBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 1;
    }

    if(CheckCollisionPointRec(GetMousePosition(), veryhardBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 3;
    }

    if(CheckCollisionPointRec(GetMousePosition(), exitBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 2;
    }
}

void Menu::Draw(Font font){

    DrawTextEx(font, "SELECT LEVEL", {300, 80}, 40, 2, WHITE);

    DrawRectangleRec(normalBtn, SKYBLUE);
    DrawTextEx(font, "NORMAL", {360, 195}, 30, 2, BLACK);

    DrawRectangleRec(hardBtn, ORANGE);
    DrawTextEx(font, "HARD", {380, 315}, 30, 2, BLACK);

    DrawRectangleRec(veryhardBtn, PURPLE);
    DrawTextEx(font, "VERY HARD", {340, 435}, 30, 2, BLACK);

    DrawRectangleRec(exitBtn, RED);
    DrawTextEx(font, "exit", {700, 10}, 30, 2, BLACK);
}

int Menu::GetDifficulty() const{

    return difficulty;

}