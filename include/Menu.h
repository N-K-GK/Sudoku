#pragma once
#include "raylib.h"

class Menu{

private:

    Rectangle normalBtn;
    Rectangle hardBtn;
    Rectangle veryhardBtn;
    Rectangle exitBtn;

    int difficulty;

public:

    Menu();

    void Update();
    void Draw(Font font);
    int GetDifficulty() const;
};