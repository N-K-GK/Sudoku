#pragma once
#include "raylib.h"

class Result{

private:

    Rectangle retryBtn;
    Rectangle select_gameBtn;

    int difficulty;

    char playerName[100];
    char resultName[100];

    int buttonResult;      // Retry or Select
    int gameDifficulty;
    int resultDifficulty;

    double clearTime;
    double resultTime;

public:

    Result();

    void Update();
    void Draw(Font font);

    void SetResult(const char name[], int difficulty, double time);
    int GetDifficulty() const;
    void Reset();
};