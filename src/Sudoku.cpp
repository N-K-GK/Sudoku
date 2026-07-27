#include "Sudoku.h"
#include "Result.h"
#include <random>

Sudoku::Sudoku(){

    selectedRow = -1;
    selectedCol = -1;
    motosuu = 0;
    masucount = 0;
    selectedNumber = 0;
    timerStop = false;
    startTime = GetTime();
    elapsedTime = 0;
    memoMode = 0;
    exitflag = 1;

}

void Sudoku::InitBoard(){
    if(sudokuMode == LARGE_SUDOKU){
        boardSize = 16;
        boardBrock = 4;
        CELL_SIZE = 50.0f;
        retireBtn = {980, 10, 80, 60};
    }else{
        boardSize = 9;
        boardBrock = 3;
        CELL_SIZE = 50.0f;
        retireBtn = {680, 10, 80, 60};
    }

    float boardPixel = boardSize * CELL_SIZE;

    START_X = (GetScreenWidth() - boardPixel) / 2.0f;
    START_Y = (GetScreenHeight() - boardPixel) / 2.0f + 50;

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            sudokuBtn[row][col] = {START_X + col * CELL_SIZE, START_Y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
        }
    }
}

void Sudoku::CreateQuestion(){
    timerStop = false;
    elapsedTime = 0;
    startTime = GetTime();

    // 全部空欄
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            question[row][col] = 0;
            answer[row][col] = 0;
        }
    }

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            answer[row][col] = (row * boardBrock + row / boardBrock + col) % boardSize + 1;
        }
    }

    for(int i = 0; i < 7; i++){ //数字交換
        int changeA = rand() % boardSize + 1;
        int changeB = rand() % boardSize + 1;
        do{
            changeB = rand() % boardSize + 1;
        } while(changeA == changeB);

        for(int row = 0; row < boardSize; row++){
            for(int col = 0; col < boardSize; col++){
                if(answer[row][col] == changeA){
                    answer[row][col] = -1;
                }else if(answer[row][col] == changeB){
                    answer[row][col] = -2;
                }
            }
        }
        for(int row = 0; row < boardSize; row++){
            for(int col = 0; col < boardSize; col++){
                if(answer[row][col] == -1){
                    answer[row][col] = changeB;
                }else if(answer[row][col] == -2){
                    answer[row][col] = changeA;
                }
            }
        }
    }

    for(int block = 0; block < boardBrock; block++){ //3行の行交換
        int change_rowA;
        int change_rowB;
        do{
            change_rowA = rand() % boardBrock;
            change_rowB = rand() % boardBrock;
        }while(change_rowA == change_rowB);

        change_rowA += block * boardBrock;
        change_rowB += block * boardBrock;

        int temp[boardSize];
        for(int col = 0; col < boardSize; col++){
            temp[col] = answer[change_rowA][col];
        }

        // A行へB行をコピー
        for(int col = 0; col < boardSize; col++){
            answer[change_rowA][col] = answer[change_rowB][col];
        }

        // B行へ保存していたA行をコピー
        for(int col = 0; col < boardSize; col++){
            answer[change_rowB][col] = temp[col];
        }
    }

    for(int block = 0; block < boardBrock; block++){ //3列の列交換
        int change_colA;
        int change_colB;
        do{
            change_colA = rand() % boardBrock;
            change_colB = rand() % boardBrock;
        }while(change_colA == change_colB);

        change_colA += block * boardBrock;
        change_colB += block * boardBrock;

        int temp[boardSize];
        for(int row = 0; row < boardSize; row++){
            temp[row] = answer[row][change_colA];
        }

        // A列へB列をコピー
        for(int row = 0; row < boardSize; row++){
            answer[row][change_colA] = answer[row][change_colB];
        }

        // B列へ保存していたA列をコピー
        for(int row = 0; row < boardSize; row++){
            answer[row][change_colB] = temp[row];
        }
    }

    for(int block = 0; block < boardBrock; block++){ //3ブロックの行交換
        int change_row_blockA;
        int change_row_blockB;
        do{
            change_row_blockA = rand() % boardBrock;
            change_row_blockB = rand() % boardBrock;
        }while(change_row_blockA == change_row_blockB);

        int startA = change_row_blockA * boardBrock;
        int startB = change_row_blockB * boardBrock;
        int temp[boardBrock][boardSize];
        for(int row = 0; row < boardBrock; row++){
            for(int col = 0; col < boardSize; col++){
                temp[row][col] = answer[startA + row][col];
            }
        }

        // BブロックをAブロックへコピー
        for(int row = 0; row < boardBrock; row++){
            for(int col = 0; col < boardSize; col++){
                answer[startA + row][col] = answer[startB + row][col];
            }
        }

        // 保存していたAブロックをBブロックへコピー
        for(int row = 0; row < boardBrock; row++){
            for(int col = 0; col < boardSize; col++){
                answer[startB + row][col] = temp[row][col];
            }
        }
    }

    for(int block = 0; block < boardBrock; block++){ //3ブロックの列交換
        int change_col_blockA;
        int change_col_blockB;
        do{
            change_col_blockA = rand() % boardBrock;
            change_col_blockB = rand() % boardBrock;
        }while(change_col_blockA == change_col_blockB);

        int startA = change_col_blockA * boardBrock;
        int startB = change_col_blockB * boardBrock;
        int temp[boardSize][boardBrock];
        for(int col = 0; col < boardBrock; col++){
            for(int row = 0; row < boardSize; row++){
                temp[row][col] = answer[row][startA + col];
            }
        }

        // BブロックをAブロックへコピー
        for(int col = 0; col < boardBrock; col++){
            for(int row = 0; row < boardSize; row++){
                answer[row][startA + col] = answer[row][startB + col];
            }
        }

        // 保存していたAブロックをBブロックへコピー
        for(int col = 0; col < boardBrock; col++){
            for(int row = 0; row < boardSize; row++){
                answer[row][startB + col] = temp[row][col];
            }
        }
    }

    int visible = 35; //最初から表示されるマス数
    if(sudokuMode == NORMAL_SUDOKU){
        if(difficulty == 0){
            visible = 35;
        }else if(difficulty == 1){
            visible = 30;
        }else if(difficulty == 3){
            visible = 25;
        }
    }else if(sudokuMode == KILLER_SUDOKU){
        if(difficulty == 0){
            visible = 25;
        }else if(difficulty == 1){
            visible = 18;
        }else if(difficulty == 3){
            visible = 0;
        }
    }else if(sudokuMode == LARGE_SUDOKU){
        if(difficulty == 0){
            visible = 130;
        }else if(difficulty == 1){
            visible = 110;
        }else if(difficulty == 3){
            visible = 90;
        }
    }

    int count = 0;
    while(count < visible){
        int row = rand() % boardSize;
        int col = rand() % boardSize;

        if(question[row][col] == 0){
            question[row][col] = answer[row][col];
            count++;
        }
    }

}

void Sudoku::CreateKillerQuestion(){

    //普通の数独解答を作成
    CreateQuestion();

    //ケージ作成
    while(true){
        if(CreateCage()){
            break;
        }
    }
}

bool Sudoku::CreateCage(){
    cageCount = 0;

    // 全マス未使用
    for(int r = 0; r < boardSize; r++){
        for(int c = 0; c < boardSize; c++){
            cageMap[r][c] = -1;
        }
    }

    // ケージサイズ一覧を作る
    int cageSize[50];
    int cageNum = 0;
    int total = 0;
    while(total < boardSize * boardSize){
        int remain = boardSize * boardSize - total;
        int size;

        if(remain <= 5){
            size = remain;
        }else{
            size = GetRandomValue(2,5);

            while(remain - size == 1){
                size = GetRandomValue(2,5);
            }
        }

        cageSize[cageNum++] = size;
        total += size;
    }

    // サイズ一覧をシャッフル
    for(int i = 0; i < cageNum; i++){
        int r = GetRandomValue(i, cageNum - 1);
        std::swap(cageSize[i], cageSize[r]);
    }

    // ケージ生成
    for(int k = 0; k < cageNum; k++){
        // 未使用マス一覧
        int rowList[boardSize * boardSize];
        int colList[boardSize * boardSize];
        int unusedCount = 0;

        for(int r = 0; r < boardSize; r++){
            for(int c = 0; c < boardSize; c++){
                if(cageMap[r][c] == -1){
                    rowList[unusedCount] = r;
                    colList[unusedCount] = c;
                    unusedCount++;
                }
            }
        }

        if(unusedCount == 0){
            break;
        } 

        // ランダム開始位置
        int start = GetRandomValue(0, unusedCount - 1);
        GrowCage(rowList[start],colList[start],cageSize[k]);

        // 作れなかったら失敗
        if(cages[cageCount].count != cageSize[k]){
            return false;
        }

        cageCount++;
    }

    // 全マス使われたか
    if(CountUnusedCell() != 0){
        return false;
    }

    // 合計計算
    for(int i = 0; i < cageCount; i++){
        cages[i].sum = 0;

        for(int j = 0; j < cages[i].count; j++){
            int row = cages[i].row[j];
            int col = cages[i].col[j];

            cages[i].sum += answer[row][col];
        }
    }

    return true;
}

void Sudoku::GrowCage(int startRow, int startCol, int targetSize){
    cages[cageCount].count = 0;

    // 最初の1マス
    cageMap[startRow][startCol] = cageCount;
    cages[cageCount].row[0] = startRow;
    cages[cageCount].col[0] = startCol;
    cages[cageCount].count = 1;

    while(cages[cageCount].count < targetSize){
        int orderCell[boardSize];
        for(int i = 0; i < cages[cageCount].count; i++){
            orderCell[i] = i;
        }
        for(int i = 0; i < cages[cageCount].count; i++){
            int r = GetRandomValue(i, cages[cageCount].count - 1);
            std::swap(orderCell[i], orderCell[r]);
        }

        bool added = false;
        // ケージ内の全マスから伸ばす
        for(int k = 0; k < cages[cageCount].count; k++){
            int index = orderCell[k];

            int row = cages[cageCount].row[index];
            int col = cages[cageCount].col[index];

            int dr[4] = {-1, 0, 1, 0};
            int dc[4] = { 0, 1, 0,-1};

            int order[4] = {0, 1, 2, 3};

            // 方向をシャッフル
            for(int i = 0; i < 4; i++){
                int r = GetRandomValue(i, 3);
                std::swap(order[i], order[r]);
            }

            // 4方向を調べる
            for(int i = 0; i < 4; i++){
                int nr = row + dr[order[i]];
                int nc = col + dc[order[i]];

                if(nr < 0 || nr >= boardSize || nc < 0 || nc >= boardSize){
                    continue;
                }

                if(cageMap[nr][nc] != -1){
                    continue;
                }

                // 新しいマスを追加
                int p = cages[cageCount].count;
                cages[cageCount].row[p] = nr;
                cages[cageCount].col[p] = nc;

                cageMap[nr][nc] = cageCount;

                cages[cageCount].count++;

                added = true;

                break;
            }

            // 1マス追加できたらwhileへ戻る
            if(added){
                break;
            }
        }

        // ケージ全体を調べても追加できない
        if(!added){
            break;
        }
    }
}

bool Sudoku::HasSingleCellCage(){
    for(int i = 0; i < cageCount; i++){
        if(cages[i].count == 1){
            return true;
        }
    }

    return false;
}

void Sudoku::MergeSingleCellCage(){
    int dr[4] = {-1, 1, 0, 0};
    int dc[4] = { 0, 0,-1, 1};

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            // 未使用マスだけ対象
            if(cageMap[row][col] != -1){
                continue;
            }

            int candidate[4];
            int candidateCount = 0;

            // 隣接ケージを集める
            for(int k = 0; k < 4; k++){
                int nr = row + dr[k];
                int nc = col + dc[k];

                if(nr < 0 || nr >= boardSize || nc < 0 || nc >= boardSize){
                    continue;
                }

                int id = cageMap[nr][nc];
                if(id == -1){
                    continue;
                }

                // 5マス以上にはしない
                if(cages[id].count >= 5){
                    continue;
                }

                // 重複防止
                bool exist = false;
                for(int i = 0; i < candidateCount; i++){
                    if(candidate[i] == id){
                        exist = true;
                        break;
                    }
                }

                if(!exist){
                    candidate[candidateCount] = id;
                    candidateCount++;
                }
            }

            // 候補があればランダムに選ぶ
            if(candidateCount > 0){
                int index = GetRandomValue(0, candidateCount - 1);
                int id = candidate[index];
                int p = cages[id].count;

                cages[id].row[p] = row;
                cages[id].col[p] = col;
                cages[id].count++;

                cageMap[row][col] = id;
            }
        }
    }
}

int Sudoku::CountUnusedCell() const{
    int count = 0;
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            if(cageMap[row][col] == -1){
                count++;
            }
        }
    }

    return count;
}

int Sudoku::GetCageIndex(int row, int col){
    for(int i = 0; i < cageCount; i++){
        for(int j = 0; j < cages[i].count; j++){
            if((int)cages[i].row[j] == row && (int)cages[i].col[j] == col){
                return i;
            }
        }
    }
    return -1;
}

void Sudoku::Update(char my_name[100], int& nameLength){
    if(!timerStop){
        elapsedTime = GetTime() - startTime;
    }

    exitflag = 1;

    if(CheckCollisionPointRec(GetMousePosition(), retireBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
        for(int i = nameLength; i > 0; i--){
            nameLength--;
            my_name[nameLength] = '\0';
        }

        for(int row = 0; row < boardSize; row++){
            for(int col = 0; col < boardSize; col++){
                selectedRow = -1;
                selectedCol = -1;
                sudokuBtn[row][col] = {START_X + col * CELL_SIZE, START_Y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE};
                board[row][col] = 0;
                for(int num = 0; num < boardSize+1; num++){
                    memo[row][col][num] = false;
                }
            }
        }

        SetWindowSize(800, 600);
        
        exitflag = 0;
    }

    DrawRectangle(START_X, START_Y, 9 * CELL_SIZE, 9 * CELL_SIZE, WHITE); //マスを白で塗りつぶす

    for(int i = 0; i <= boardSize; i++){
        float thick;
        if(i % boardBrock == 0){
            thick = 3.5f;
        }else{
            thick = 1.10f;
        }

        // 縦線
        DrawLineEx({START_X + i * CELL_SIZE, START_Y}, {START_X + i * CELL_SIZE, START_Y + 9 * CELL_SIZE}, thick, BLACK);

        // 横線
        DrawLineEx({START_X, START_Y + i * CELL_SIZE}, {START_X + 9 * CELL_SIZE, START_Y + i * CELL_SIZE}, thick, BLACK);
    }

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            Rectangle cell = {START_X + col * CELL_SIZE, START_Y + row * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            if(CheckCollisionPointRec(GetMousePosition(), cell) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                selectedRow = row;
                selectedCol = col;
                memoMode = 0;

                if(question[row][col] != 0){
                    selectedNumber = question[row][col];
                }else{
                    selectedNumber = board[row][col];
                }
            }

            if(CheckCollisionPointRec(GetMousePosition(), cell) && IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)){
                selectedRow = row;
                selectedCol = col;
                memoMode = 1;
            }
        }
    }

    if (selectedRow != -1 && selectedCol != -1 && memoMode == 0){
        if(IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)){
            board[selectedRow][selectedCol] = 1;
            selectedNumber = 1;
        }else if(IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)){
            board[selectedRow][selectedCol] = 2;
            selectedNumber = 2;
        }else if(IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)){
            board[selectedRow][selectedCol] = 3;
            selectedNumber = 3;
        }else if(IsKeyPressed(KEY_FOUR) || IsKeyPressed(KEY_KP_4)){
            board[selectedRow][selectedCol] = 4;
            selectedNumber = 4;
        }else if(IsKeyPressed(KEY_FIVE) || IsKeyPressed(KEY_KP_5)){
            board[selectedRow][selectedCol] = 5;
            selectedNumber = 5;
        }else if(IsKeyPressed(KEY_SIX) || IsKeyPressed(KEY_KP_6)){
            board[selectedRow][selectedCol] = 6;
            selectedNumber = 6;
        }else if(IsKeyPressed(KEY_SEVEN) || IsKeyPressed(KEY_KP_7)){
            board[selectedRow][selectedCol] = 7;
            selectedNumber = 7;
        }else if(IsKeyPressed(KEY_EIGHT) || IsKeyPressed(KEY_KP_8)){
            board[selectedRow][selectedCol] = 8;
            selectedNumber = 8;
        }else if(IsKeyPressed(KEY_NINE) || IsKeyPressed(KEY_KP_9)){
            board[selectedRow][selectedCol] = 9;
            selectedNumber = 9;
        }else if(IsKeyPressed(KEY_A) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 10;
            selectedNumber = 10;
        }else if(IsKeyPressed(KEY_B) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 11;
            selectedNumber = 11;
        }else if(IsKeyPressed(KEY_C) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 12;
            selectedNumber = 12;
        }else if(IsKeyPressed(KEY_D) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 13;
            selectedNumber = 13;
        }else if(IsKeyPressed(KEY_E) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 14;
            selectedNumber = 14;
        }else if(IsKeyPressed(KEY_F) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 15;
            selectedNumber = 15;
        }else if(IsKeyPressed(KEY_G) && sudokuMode == LARGE_SUDOKU){
            board[selectedRow][selectedCol] = 16;
            selectedNumber = 16;
        }else if(IsKeyPressed(KEY_ZERO) || IsKeyPressed(KEY_KP_0)){
            board[selectedRow][selectedCol] = 0;
            selectedNumber = 0;
        }if(IsKeyPressed(KEY_SEMICOLON)){

            DeleteMemoByBoard();
        }
        int inputNum = board[selectedRow][selectedCol];
        DeleteMemo(selectedRow, selectedCol, inputNum);
    }

    if (selectedRow != -1 && selectedCol != -1 && memoMode == 1){
        if(IsKeyPressed(KEY_ONE) || IsKeyPressed(KEY_KP_1)){
            memo[selectedRow][selectedCol][1] = !memo[selectedRow][selectedCol][1];
            if(memo[selectedRow][selectedCol][1]){ //追加した場合
                selectedNumber = 1;
            }
        }else if(IsKeyPressed(KEY_TWO) || IsKeyPressed(KEY_KP_2)){
            memo[selectedRow][selectedCol][2] = !memo[selectedRow][selectedCol][2];
            if(memo[selectedRow][selectedCol][2]){ //追加した場合
                selectedNumber = 2;
            }
        }else if(IsKeyPressed(KEY_THREE) || IsKeyPressed(KEY_KP_3)){
            memo[selectedRow][selectedCol][3] = !memo[selectedRow][selectedCol][3];
            if(memo[selectedRow][selectedCol][3]){ //追加した場合
                selectedNumber = 3;
            }
        }else if(IsKeyPressed(KEY_FOUR) || IsKeyPressed(KEY_KP_4)){
            memo[selectedRow][selectedCol][4] = !memo[selectedRow][selectedCol][4];
            if(memo[selectedRow][selectedCol][4]){
                //追加した場合
                selectedNumber = 4;
            }
        }else if(IsKeyPressed(KEY_FIVE) || IsKeyPressed(KEY_KP_5)){
            memo[selectedRow][selectedCol][5] = !memo[selectedRow][selectedCol][5];
            if(memo[selectedRow][selectedCol][5]){
                //追加した場合
                selectedNumber = 5;
            }
        }else if(IsKeyPressed(KEY_SIX) || IsKeyPressed(KEY_KP_6)){
            memo[selectedRow][selectedCol][6] = !memo[selectedRow][selectedCol][6];
            if(memo[selectedRow][selectedCol][6]){
                //追加した場合
                selectedNumber = 6;
            }
        }else if(IsKeyPressed(KEY_SEVEN) || IsKeyPressed(KEY_KP_7)){
            memo[selectedRow][selectedCol][7] = !memo[selectedRow][selectedCol][7];
            if(memo[selectedRow][selectedCol][7]){
                //追加した場合
                selectedNumber = 7;
            }
        }else if(IsKeyPressed(KEY_EIGHT) || IsKeyPressed(KEY_KP_8)){
            memo[selectedRow][selectedCol][8] = !memo[selectedRow][selectedCol][8];
            if(memo[selectedRow][selectedCol][8]){
                //追加した場合
                selectedNumber = 8;
            }
        }else if(IsKeyPressed(KEY_NINE) || IsKeyPressed(KEY_KP_9)){
            memo[selectedRow][selectedCol][9] = !memo[selectedRow][selectedCol][9];
            if(memo[selectedRow][selectedCol][9]){
                //追加した場合
                selectedNumber = 9;
            }
        }else if(IsKeyPressed(KEY_A) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][10] = !memo[selectedRow][selectedCol][10];
            if(memo[selectedRow][selectedCol][10]){
                //追加した場合
                selectedNumber = 10;
            }
        }else if(IsKeyPressed(KEY_B) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][11] = !memo[selectedRow][selectedCol][11];
            if(memo[selectedRow][selectedCol][11]){
                //追加した場合
                selectedNumber = 11;
            }
        }else if(IsKeyPressed(KEY_C) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][12] = !memo[selectedRow][selectedCol][12];
            if(memo[selectedRow][selectedCol][12]){
                //追加した場合
                selectedNumber = 12;
            }
        }else if(IsKeyPressed(KEY_D) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][13] = !memo[selectedRow][selectedCol][13];
            if(memo[selectedRow][selectedCol][13]){
                //追加した場合
                selectedNumber = 13;
            }
        }else if(IsKeyPressed(KEY_E) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][14] = !memo[selectedRow][selectedCol][14];
            if(memo[selectedRow][selectedCol][14]){
                //追加した場合
                selectedNumber = 14;
            }
        }else if(IsKeyPressed(KEY_F) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][15] = !memo[selectedRow][selectedCol][15];
            if(memo[selectedRow][selectedCol][15]){
                //追加した場合
                selectedNumber = 15;
            }
        }else if(IsKeyPressed(KEY_G) && sudokuMode == LARGE_SUDOKU){
            memo[selectedRow][selectedCol][16] = !memo[selectedRow][selectedCol][16];
            if(memo[selectedRow][selectedCol][16]){
                //追加した場合
                selectedNumber = 16;
            }
        }else if(IsKeyPressed(KEY_ZERO) || IsKeyPressed(KEY_KP_0)){
            bool hasMemo = false;
            // メモがあるか確認
            for(int num = 1; num <= boardSize; num++){
                if(memo[selectedRow][selectedCol][num]){
                    hasMemo = true;
                    break;
                }
            }
            
            if(hasMemo){
                // メモがあるなら全部消す
                for(int num = 1; num <= boardSize; num++){
                    memo[selectedRow][selectedCol][num] = false;
                }
            }else if(question[selectedRow][selectedCol] == 0 && board[selectedRow][selectedCol] == 0){
                // メモが無く、空マスなら1～9を全部入れる
                for(int num = 1; num <= boardSize; num++){
                    memo[selectedRow][selectedCol][num] = true;
                }
            }
        }else if(IsKeyPressed(KEY_SEMICOLON)){
            for(int row = 0; row < boardSize; row++){
                for(int col = 0; col < boardSize; col++){
                    // 問題数字・確定数字があるマスは対象外
                    if(question[row][col] != 0 || board[row][col] != 0){
                        continue;
                    }
                    // メモが1つでもあるか調べる
                    bool hasMemo = false;
                    for(int num = 1; num <= boardSize; num++){
                        if(memo[row][col][num]){
                            hasMemo = true;
                            break;
                        }
                    }
                    // メモが既にあるなら対象外
                    if(hasMemo){
                        continue;
                    }
                    // メモを1～9すべて入れる
                    for(int num = 1; num <= boardSize; num++){
                        memo[row][col][num] = true;
                    }
                }
            }
        }
    }

    if(CheckClear()){
        timerStop = true;
        exitflag = 2;
    }

    minute = (int)elapsedTime / 60;
    second = (int)elapsedTime % 60;
}

void Sudoku::Draw(Font font, int difficulty, const char my_name[]){

    const char *title;
    if(sudokuMode == NORMAL_SUDOKU){
        title = "SUDOKU";
    }else if(sudokuMode == KILLER_SUDOKU){
        title = "KILLER SUDOKU";
    }else{
        title = "LARGE SUDOKU";
    }

    int titleWidth = MeasureText(title,40);
    DrawText(title, (GetScreenWidth() - titleWidth) / 2, 20, 40, WHITE);
    
    DrawRectangleRec(retireBtn, RED);
    if(sudokuMode == LARGE_SUDOKU){
        DrawTextEx(font, "Retire", {980, 15}, 25, 2, BLACK);
    }else{
        DrawTextEx(font, "Retire", {680, 15}, 25, 2, BLACK);
    }

    DrawText(TextFormat("%02d:%02d", minute, second), 20, 20, 30, WHITE);

    DrawText(TextFormat("Name : %s", my_name), 20, 55, 25, WHITE);

    const char* difficultyText;
    switch(difficulty){

    case 0:
        difficultyText = "NORMAL";
        break;
    case 1:
        difficultyText = "HARD";
        break;
    case 3:
        difficultyText = "VERY HARD";
        break;
    default:
        difficultyText = "UNKNOWN";
        break;
    }

    DrawText(TextFormat("LEVEL : %s", difficultyText), GetScreenWidth()/ 2 - 100, 70, 25, WHITE);

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            int num = 0;
            if(question[row][col] != 0){
                num = question[row][col];
            }else{
                num = board[row][col];
            }

            // マスの色分け
            if(IsConflict(row, col)){
                DrawRectangleRec(sudokuBtn[row][col], RED);
            }else if(row == selectedRow && col == selectedCol && memoMode == 0){
                // 選択中のマス
                DrawRectangleRec(sudokuBtn[row][col], YELLOW);
            }else if(row == selectedRow && col == selectedCol && memoMode == 1){
                // 選択中のマス
                DrawRectangleRec(sudokuBtn[row][col], SKYBLUE);
            }else if(selectedNumber != 0 && num == selectedNumber){
                // 同じ数字のマス
                DrawRectangleRec(sudokuBtn[row][col], ORANGE);
            }else{
                // 通常
                DrawRectangleRec(sudokuBtn[row][col], WHITE);
            }

            if(question[row][col] != 0){
                DrawText(TextFormat("%d", question[row][col]), START_X + col * CELL_SIZE + 18, START_Y + row * CELL_SIZE + 10, 30, RED);
            }else if(board[row][col] != 0){
                DrawText(TextFormat("%d", board[row][col]), START_X + col * CELL_SIZE + 18, START_Y + row * CELL_SIZE + 10, 30, BLACK);
            }else{
                for(int num = 1; num <= boardSize; num++){
                    if(memo[row][col][num]){
                        Color memoColor = BLACK;
                        Color cellColor = ORANGE;
                        
                        cellX = START_X + col * CELL_SIZE;
                        cellY = START_Y + row * CELL_SIZE;

                        int gridSize;
                        int num_size;
                        int rectangle_size;
                        if(sudokuMode == LARGE_SUDOKU){
                            gridSize = 4;
                            num_size = 6;
                            rectangle_size = 8;
                        }else{
                            gridSize = 3;
                            num_size = 11;
                            rectangle_size = 11;
                        }

                        if(sudokuMode == KILLER_SUDOKU){
                            switch (num){

                            case 1: 
                                if(selectedNumber == 1){ 
                                    DrawRectangle(cellX + 17, cellY + 11, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("1", cellX + 23, cellY + 12, num_size, memoColor); 
                                break; 
                            case 2: 
                                if(selectedNumber == 2){ 
                                    DrawRectangle(cellX + 25, cellY + 11, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("2", cellX + 28, cellY + 12, num_size, memoColor); 
                                break; 
                            case 3: 
                                if(selectedNumber == 3){ 
                                    DrawRectangle(cellX + 33, cellY + 11, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("3", cellX + 36, cellY + 12, num_size, memoColor); 
                                break; 
                            case 4: 
                                if(selectedNumber == 4){ 
                                    DrawRectangle(cellX + 17, cellY + 23, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("4", cellX + 20, cellY + 24, num_size, memoColor); 
                                break; 
                            case 5: 
                                if(selectedNumber == 5){ 
                                    DrawRectangle(cellX + 25, cellY + 23, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("5", cellX + 28, cellY + 24, num_size, memoColor); 
                                break; 
                            case 6: 
                                if(selectedNumber == 6){ 
                                    DrawRectangle(cellX + 33, cellY + 23, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("6", cellX + 36, cellY + 24, num_size, memoColor); 
                                break; 
                            case 7: 
                                if(selectedNumber == 7){ 
                                    DrawRectangle(cellX + 17, cellY + 33, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("7", cellX + 20, cellY + 34, num_size, memoColor); 
                                break; 
                            case 8: 
                                if(selectedNumber == 8){ 
                                    DrawRectangle(cellX + 25, cellY + 33, rectangle_size, rectangle_size, cellColor);
                                } 
                                DrawText("8", cellX + 28, cellY + 34, num_size, memoColor); 
                                break; 
                            case 9: 
                                if(selectedNumber == 9){ 
                                    DrawRectangle(cellX + 33, cellY + 33, rectangle_size, rectangle_size, cellColor); 
                                } 
                                DrawText("9", cellX + 36, cellY + 34, num_size, memoColor); 
                                break; 
                            default: 
                                break; 
                            }

                        }else{
                            // メモ配置
                            int memoRow;
                            int memoCol;

                            float space;
                            float offsetX;
                            float offsetY;

                            // NORMAL
                            if(sudokuMode == NORMAL_SUDOKU){

                                int index = num - 1;

                                memoRow = index / 3;
                                memoCol = index % 3;

                                space = CELL_SIZE / 3.0f;
                                offsetX = 3;
                                offsetY = 2;

                                num_size = 11;
                                rectangle_size = 11;

                            }else{ // LARGE

                                int index = num - 1;

                                memoRow = index / 4;
                                memoCol = index % 4;

                                space = CELL_SIZE / 5.0f;
                                offsetX = 3;
                                offsetY = 2;

                                num_size = 6;
                                rectangle_size = 7;

                            }

                            // 選択中の強調
                            if(selectedNumber == num){
                                DrawRectangle(cellX + offsetX + memoCol * space, cellY + offsetY + memoRow * space, rectangle_size, rectangle_size, cellColor);
                            }

                            // 表示文字
                            const char* text;
                            if(num <= 9){
                                text = TextFormat("%d", num);
                            }else{
                                text = TextFormat("%c", 'A' + num - 10);
                            }

                            DrawText(text,cellX + offsetX + memoCol * space + 2, cellY + offsetY + memoRow * space, num_size, memoColor);
                        }
                    }
                }
            }    
        }
    }

    for(int i = 0; i <= boardSize; i++){
        float thick;
        if(i % boardBrock == 0){
            thick = 3.5f;
        }else{
            thick = 1.10f;
        }

        // 縦線
        DrawLineEx({START_X + i * CELL_SIZE, START_Y}, {START_X + i * CELL_SIZE, START_Y + boardSize * CELL_SIZE}, thick, BLACK);

        // 横線
        DrawLineEx({START_X, START_Y + i * CELL_SIZE}, {START_X + boardSize * CELL_SIZE, START_Y + i * CELL_SIZE}, thick, BLACK);
    }

    if(sudokuMode == KILLER_SUDOKU){
        Color cageColor = MAGENTA;
        for(int i = 0; i < cageCount; i++){

            if(cages[i].count == 0){
                continue;
            }

            // ケージ内の左上セルを探す
            int row = boardSize;
            int col = boardSize;
            for(int j = 0; j < cages[i].count; j++){
                int r = cages[i].row[j];
                int c = cages[i].col[j];

                if(r < row || (r == row && c < col)){
                    row = r;
                    col = c;
                }
            }

            DrawText(TextFormat("%d", cages[i].sum), START_X + col * CELL_SIZE + 5, START_Y + row * CELL_SIZE + 4, 15, BLACK);
        }

        for(int row = 0; row < boardSize; row++){
            for(int col = 0; col < boardSize; col++){
                int now = GetCageIndex(row,col);
                float x = START_X + col*CELL_SIZE;
                float y = START_Y + row*CELL_SIZE;
                float difference = 4;

                // 上
                if(row == 0 || GetCageIndex(row - 1, col) != now){
                    DrawLine(x + difference, y + difference, x + CELL_SIZE - difference, y + difference, cageColor);
                }

                // 左
                if(col == 0 || GetCageIndex(row, col - 1) != now){
                    DrawLine(x + difference, y + difference, x + difference, y + CELL_SIZE - difference, cageColor);
                }

                // 下
                if(row == 8 || GetCageIndex(row + 1, col) != now){
                    DrawLine(x + difference, y + CELL_SIZE - difference, x + CELL_SIZE - difference, y + CELL_SIZE - difference, cageColor);
                }

                // 右
                if(col == 8 || GetCageIndex(row, col + 1) != now){
                    DrawLine(x + CELL_SIZE - difference, y + difference, x + CELL_SIZE - difference, y + CELL_SIZE - difference, cageColor);
                }
            }
        }
    }
}

void Sudoku::DeleteMemo(int row, int col, int num){
    for(int i = 0; i < boardSize; i++){
        if(memo[row][i][num]){
            memo[row][i][num] = false;
        }

        if(memo[i][col][num]){
            memo[i][col][num] = false;
        }
    }
        
    int startRow = (row / boardBrock) * boardBrock;
    int startCol = (col / boardBrock) * boardBrock;
    for(int r = startRow; r < startRow + boardBrock; r++){
        for(int c = startCol; c < startCol + boardBrock; c++){
            memo[r][c][num] = false;
        }
    }
}

void Sudoku::DeleteMemoByBoard(){
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){

            int num = 0;
            // 確定数字取得
            if(question[row][col] != 0){
                num = question[row][col];
            }else if(board[row][col] != 0){
                num = board[row][col];
            }

            // 数字がない場合は無視
            if(num == 0){
                continue;
            }

            // 同じ行と列のメモ削除
            for(int c = 0; c < boardSize; c++){
                memo[row][c][num] = false;
                memo[c][col][num] = false;
            }

            // 同じブロックのメモ削除
            int startRow = (row / boardBrock) * boardBrock;
            int startCol = (col / boardBrock) * boardBrock;
            for(int r = 0; r < boardBrock; r++){
                for(int c = 0; c < boardBrock; c++){
                    memo[startRow + r][startCol + c][num] = false;
                }
            }
        }
    }
}

void Sudoku::UpdateSelectedNumber(){

    selectedNumber = 0;
    if(selectedRow == -1 || selectedCol == -1){
        return;
    }

    //通常数字が入っている場合
    if(question[selectedRow][selectedCol] != 0){
        selectedNumber = question[selectedRow][selectedCol];
        return;
    }

    if(board[selectedRow][selectedCol] != 0){
        selectedNumber = board[selectedRow][selectedCol];
        return;
    }

    //メモを確認
    for(int num = 1; num <= boardSize; num++){
        if(memo[selectedRow][selectedCol][num]){
            selectedNumber = num;
            return;
        }
    }
}

bool Sudoku::IsConflict(int row, int col){
    if(question[row][col] != 0){
        return false;
    }

    int num;
    if(question[row][col] != 0){
        num = question[row][col];
    }else{
        num = board[row][col];
    }

    // 空マスは対象外
    if(num == 0){
        return false;
    }

    // 行
    for(int c = 0; c < boardSize; c++){
        if(c == col){
            continue;
        }

        int n;
        if(question[row][c] != 0){
            n = question[row][c];
        }else{
            n = board[row][c];
        }

        if(n == num){
            return true;
        }
    }

    // 列
    for(int r = 0; r < boardSize; r++){
        if(r == row){
            continue;
        }

        int n;
        if(question[r][col] != 0){
            n = question[r][col];
        }else{
            n = board[r][col];
        }

        if(n == num){
            return true;
        }
    }

    // ブロック
    int startRow = (row / boardBrock) * boardBrock;
    int startCol = (col / boardBrock) * boardBrock;
    for(int r = startRow; r < startRow + boardBrock; r++){
        for(int c = startCol; c < startCol + boardBrock; c++){
            if(r == row && c == col){
                continue;
            }

            int n;
            if(question[r][c] != 0){
                n = question[r][c];
            }else{
                n = board[r][c];
            }

            if(n == num){
                return true;
            }
        }
    }

    return false;
}

bool Sudoku::CheckCage(){
    for(int i = 0; i < cageCount; i++){
        if(cages[i].count == 0){
            continue;
        }

        int sum = 0;
        for(int j = 0; j < cages[i].count; j++){
            int row=(int)cages[i].row[j];
            int col=(int)cages[i].col[j];
            if(question[row][col] != 0){
                sum += question[row][col];
            }else{
                sum += board[row][col];
            }
        }

        if(sum != cages[i].sum){
            return false;
        }
    }
    return true;
}

bool Sudoku::CheckClear(){
    int num;
    for(int row = 0; row < boardSize; row++){ //盤面が埋まっているか?
        for(int col = 0; col < boardSize; col++){
            if(question[row][col] == 0 && board[row][col] == 0){
                return false;
            }
        }
    }

    for(int row = 0; row < boardSize; row++){ //行判定
        bool used[boardSize + 1] = {false};
        for(int col = 0; col < boardSize; col++){
            num = 0;
            if(question[row][col] != 0){
                num = question[row][col];
            }else{
                num = board[row][col];
            }

            if(num < 1 || num > boardSize){
                return false;
            }

            // 同じ数字が既にあれば失敗
            if(used[num]){
                return false;
            }

            used[num] = true;
        }
    }

    for(int col = 0; col < boardSize; col++){ //列判定
        bool used[boardSize + 1] = {false};
        for(int row = 0; row < boardSize; row++){
            num = 0;
            if(question[row][col] != 0){
                num = question[row][col];
            }else{
                num = board[row][col];
            }

            if(num < 1 || num > boardSize){
                return false;
            }

            // 同じ数字が既にあれば失敗
            if(used[num]){
                return false;
            }
            used[num] = true;
        }
    }

    for(int blockRow = 0; blockRow < boardBrock; blockRow++){ //3×3判定
        for(int blockCol = 0; blockCol < boardBrock; blockCol++){
            bool used[boardBrock * boardBrock + 1] = {false};

            for(int row = 0; row < boardBrock; row++){
                for(int col = 0; col < boardBrock; col++){
                    int r = blockRow * boardBrock + row;
                    int c = blockCol * boardBrock + col;

                    num = 0;
                    if(question[r][c] != 0){
                        num = question[r][c];
                    }else{
                        num = board[r][c];
                    }

                    if(num < 1 || num > boardSize){
                        return false;
                    }

                    if(used[num]){
                        // 同じ数字があった
                        return false;
                    }
                    used[num] = true;
                }
            }
        }
    }

    if(sudokuMode == KILLER_SUDOKU){
        if(!CheckCage()){
            return false;
        }
    }
    return true;
}

int Sudoku::GetDifficulty(){

    return exitflag;

}

void Sudoku::SetDifficulty(int d){

    difficulty = d;

}

double Sudoku::GetElapsedTime() const{

    return elapsedTime;

}

int Sudoku::GetDifficultyMode() const{

    return difficulty;

}

void Sudoku::ResetBoard(){
    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            board[row][col] = 0;
            for(int num = 0; num < boardSize + 1; num++){
                memo[row][col][num] = false;
            }
        }
    }

    for(int row = 0; row < boardSize; row++){
        for(int col = 0; col < boardSize; col++){
            question[row][col] = 0;
            answer[row][col] = 0;
        }
    }

    selectedRow = -1;
    selectedCol = -1;
    selectedNumber = 0;
    memoMode = 0;
    exitflag = 1;
    minute = 0;
    second = 0;

}

void Sudoku::ResetTimer(){

    timerStop = false;
    elapsedTime = 0;
    startTime = GetTime();
    minute = 0;
    second = 0;

}

void Sudoku::StartGame(){
    if(sudokuMode == LARGE_SUDOKU){
        SetWindowSize(1100, 950);
    }else{
        SetWindowSize(800, 600);
    }

    ResetBoard();
    ResetTimer();

    InitBoard();
    if(sudokuMode == KILLER_SUDOKU){
        CreateKillerQuestion();
    }else{
        CreateQuestion();

    }
}

void Sudoku::SetSudokuFlag(int flag){

    if(flag == 0){
        sudokuMode = NORMAL_SUDOKU;
    }else if(flag == 1){
        sudokuMode = KILLER_SUDOKU;
    }else if(flag == 2){
        sudokuMode = LARGE_SUDOKU;
    }
}

int Sudoku::GetSudokuFlag() const{

    return (int)sudokuMode;

}

Sudoku::SudokuMode Sudoku::GetSudokuMode() const{

    return sudokuMode;

}