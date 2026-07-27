#include "Result.h"
#include <cstring>

Result::Result(){

    retryBtn = {30, 500, 300, 60};
    select_gameBtn = {440, 500, 300, 60};

    difficulty = -1;
}

void Result::Update(){

    difficulty = -1;

    if(CheckCollisionPointRec(GetMousePosition(), retryBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 0;
    }

    if(CheckCollisionPointRec(GetMousePosition(), select_gameBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        difficulty = 1;
        SetWindowSize(800, 600);
    }
}

void Result::Draw(Font font){

    DrawTextEx(font, "GAME CLEAR!", {300, 30}, 40, 2, YELLOW);

    DrawTextEx(font, "Result", {360, 80}, 40, 2, WHITE);

    DrawTextEx(font, TextFormat("Name : %s", resultName), {280, 170}, 30, 2, WHITE);

    const char* diff = "";
    if(resultDifficulty == 0){
        diff = "NORMAL";
    }else if(resultDifficulty == 1){
        diff = "HARD";
    }else if(resultDifficulty == 3){
        diff = "VERY HARD";
    }else{
        diff = "UNKNOWN";
    }
    DrawTextEx(font, TextFormat("Select Level : %s", diff), {280, 230}, 30, 2, WHITE);

    int minute = (int)resultTime / 60;
    int second = (int)resultTime % 60;
    DrawTextEx(font, TextFormat("Time : %02d:%02d", minute,second), {280, 290}, 30, 2, WHITE);

    

    DrawRectangleRec(retryBtn, DARKBLUE);
    DrawTextEx(font, "Retry", {140, 520}, 30, 2, WHITE);

    DrawRectangleRec(select_gameBtn, ORANGE);
    DrawTextEx(font, "Select Game", {515, 520}, 30, 2, WHITE);
}

int Result::GetDifficulty() const{

    return difficulty;

}

void Result::SetResult(const char name[], int difficulty, double time){

    strcpy(resultName, name);
    resultDifficulty = difficulty;
    resultTime = time;

}

void Result::Reset(){

    difficulty = -1;
    resultDifficulty = -1;
    resultTime = 0;
    resultName[0] = '\0';

}