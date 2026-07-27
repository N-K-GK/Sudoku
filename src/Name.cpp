#include "Name.h"

Name::Name(){

    enterBtn = {620, 250, 100, 60};
    namebox = {200, 250, 400, 50};
    exitBtn = {680, 10, 80, 60};
}

void Name::Update(char my_name[100], int& nameLength){
    exitflag = 1;

    if(CheckCollisionPointRec(GetMousePosition(), exitBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        for(int i = nameLength; i > 0; i--){
            nameLength--;
            my_name[nameLength] = '\0';
        }
        exitflag = 0;
    }

    if(CheckCollisionPointRec(GetMousePosition(), enterBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        exitflag = 2;
    }

    DrawText(my_name, namebox.x + 10, namebox.y + 10, 30, WHITE);

    int key = GetCharPressed();
    while(key > 0){
        if(key >= 32 && key <= 125){
            if(nameLength < 99){
                my_name[nameLength] = (char)key;
                nameLength++;
                my_name[nameLength] = '\0';
            }
        }
        key = GetCharPressed();
    }

    if(IsKeyPressed(KEY_BACKSPACE)){
        if(nameLength > 0){
            nameLength--;
            my_name[nameLength] = '\0';
        }
    }
}

void Name::Draw(Font font){

    DrawTextEx(font, "ENTER YOUR NAME", {270, 80}, 40, 2, WHITE);

    DrawRectangleLinesEx(namebox, 2, WHITE);

    DrawRectangleRec(enterBtn, GRAY);
    DrawTextEx(font, "Start", {630, 260}, 30, 2, WHITE);

    DrawRectangleRec(exitBtn, RED);
    DrawTextEx(font, "exit", {700, 10}, 30, 2, BLACK);
}

int Name::GetDifficulty(){

    return exitflag;

}

void Name::Reset(char my_name[100], int& nameLength){

    my_name[0] = '\0';
    nameLength = 0;

}