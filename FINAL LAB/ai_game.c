#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

void printboard(char board[3][3])
{

    printf("-----------\n");
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            printf("%c | ", board[i][j]);
        }
        printf("\n-----------\n");
    }
}

int isfull(char board[3][3])
{

    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (board[i][j] == ' ')
            {
                return 0;
            }
        }
    }
    return 1;
}

int checkwin(char board[3][3], char x){
    for (int i = 0; i < 3; ++i){
        // Check horizontally
        if (board[i][0] == x && board[i][1] == x && board[i][2] == x)
            return 1;
        // Check vertically
        if (board[0][i] == x && board[1][i] == x && board[2][i] == x)
            return 1;
    }
    // Check diaganol
    if (board[0][0] == x && board[1][1] == x && board[2][2] == x)
        return 1;
    // Check anti-diaganol
    if (board[0][2] == x && board[1][1] == x && board[2][0] == x)
        return 1;
    return 0;
}

int minmax(char board[3][3], int depth, int ismaxi){
    if (checkwin(board, 'O'))
        return 9 - depth;
    if (checkwin(board, 'X'))
        return depth - 9;
    if (isfull(board))
        return 0;
    // Human - '1', AI - '0'
    if (ismaxi){
        int bestscore = INT_MIN;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (board[i][j] == ' '){
                    board[i][j] = 'O';
                    int score = minmax(board, depth + 1, 0);
                    board[i][j] = ' ';
                    if (score > bestscore)
                        bestscore = score;
                }
            }
        }
        return bestscore;
    }
    else{
        int bestscore = INT_MAX;
        for (int i = 0; i < 3; ++i){
            for (int j = 0; j < 3; ++j){
                if (board[i][j] == ' '){
                    board[i][j] = 'X';
                    int score = minmax(board, depth + 1, 1);
                    board[i][j] = ' ';
                    if (score < bestscore)
                        bestscore = score;
                }
            }
        }
        return bestscore;
    }
}

void AI(char board[3][3]){
    int bestscore = INT_MIN;
    int bestmove[2] = {-1, -1};
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (board[i][j] == ' '){
                board[i][j] = 'O';
                int score = minmax(board, 0, 0);
                board[i][j] = ' ';
                if (score > bestscore){
                    bestscore = score;
                    bestmove[0] = i;
                    bestmove[1] = j;
                }
            }
        }
    }
    if (bestmove[0] != -1 && bestmove[1] != -1){
        board[bestmove[0]][bestmove[1]] = 'O';
    }
}

int main(){
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    int turn = 1;
    while(1){
        printboard(board);
        if (turn == 1){
            int move;
            printf("Enter move 1-9: ");
            scanf("%d", &move);

            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            if (board[row][col] == ' ')
            {
                board[row][col] = 'X';
            }
            else
            {
                printf("Invalid move! \n");
                continue;
            }
            turn = 0;
        }
        else{
            AI(board);
            turn = 1;
        }

        if (checkwin(board, 'X')){
            printboard(board);
            printf("You win!");
            break;
        }
        else if (checkwin(board, 'O')){
            printboard(board);
            printf("Computer wins!");
            break;
        }
        else if (isfull(board)){
            printboard(board);
            printf("Draw!");
            break;
        }
    }
}
