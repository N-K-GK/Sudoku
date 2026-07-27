#pragma once
#include "raylib.h"

class Name{

private:

    Rectangle enterBtn;
    Rectangle namebox;
    Rectangle exitBtn;

    int exitflag;

public:

    Name();

    void Update(char my_name[100], int& nameLength);
    void Draw(Font font);
    
    int GetDifficulty();
    void Reset(char my_name[100], int& nameLength);
};