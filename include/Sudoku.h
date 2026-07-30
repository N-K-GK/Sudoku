#pragma once
#include "raylib.h"

class Sudoku{

private:

    Rectangle retireBtn;

    int exitflag;

    float START_X;
    float START_Y;
    float CELL_SIZE;
    float cellX;
    float cellY;

    int selectedRow;
    int selectedCol;

    static constexpr int MAX_BOARD_SIZE = 16;

    Rectangle sudokuBtn[MAX_BOARD_SIZE][MAX_BOARD_SIZE];

    int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int question[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    int answer[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    bool memo[MAX_BOARD_SIZE][MAX_BOARD_SIZE][MAX_BOARD_SIZE + 1];

    int solutionCount;  // 解の数

    int boardSize;
    int boardBrock;
    int memoMode;
    int difficulty;
    int motosuu;
    int masucount;
    int selectedNumber;

    double startTime;
    double elapsedTime;
    int minute = (int)elapsedTime / 60;
    int second = (int)elapsedTime % 60;
    bool timerStop;

    enum SudokuMode{
        NORMAL_SUDOKU = 0,
        KILLER_SUDOKU = 1,
        LARGE_SUDOKU = 2,
        KILLER_LARGE_SUDOKU = 3
    };

    SudokuMode sudokuMode = NORMAL_SUDOKU;

    struct Cage{
        int sum; // 合計
        int count;  // マス数
        int row[MAX_BOARD_SIZE * MAX_BOARD_SIZE];
        int col[MAX_BOARD_SIZE * MAX_BOARD_SIZE]; // 最大16マス
    };

    Cage cages[256];
    int cageCount;
    int cageMap[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    bool visited[MAX_BOARD_SIZE][MAX_BOARD_SIZE];
    
public:

    Sudoku();

    void InitBoard();
    void CreateQuestion();
    void CreateKillerQuestion();
    bool CreateCage();
    bool CreateLargeCage();
    void GrowCage(int startRow, int startCol, int targetSize);
    void GrowLargeCage(int startRow, int startCol, int target);
    bool HasSingleCellCage();
    void MergeSingleCellCage();
    void CompressCage();
    int CountUnusedCell() const;
    int GetCageIndex(int row, int col);

    void Update(char my_name[100], int& nameLength);
    void Draw(Font font, int difficulty, const char my_name[]);

    void DeleteMemo(int row, int col, int num);
    void DeleteMemoByBoard();
    void UpdateSelectedNumber();
    bool IsConflict(int row, int col);

    bool CheckCage();
    bool CheckClear();
    int GetDifficulty();
    void SetDifficulty(int d);
    double GetElapsedTime() const;
    int GetDifficultyMode() const;

    void ResetBoard();
    void ResetTimer();
    void StartGame();

    void SetSudokuFlag(int flag);
    int GetSudokuFlag() const;
    SudokuMode GetSudokuMode() const;

    void SolveCount(int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE]);
    bool CanPlace(int board[MAX_BOARD_SIZE][MAX_BOARD_SIZE], int row, int col, int num);
    bool CheckUnique();
};