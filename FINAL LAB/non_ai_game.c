#include <stdio.h>
#include <stdlib.h>

void printboard(char board[3][3]){
    printf("-------------\n");
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            printf(" %c |", board[i][j]);
        }
        printf("\n-------------");
        printf("\n");
    }
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

int isfull(char board[3][3]){
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (board[i][j] == ' '){
                return 0;
            }
        }
    }
    return 1;
}

void AI(char board[3][3]){
    int bestscore = -1;
    
    int magic[3][3] = {{2, 9, 4}, {7, 5, 3}, {6, 1, 8}};
    int row, col;
    for (int i = 0; i < 3; ++i){
        for (int j = 0; j < 3; ++j){
            if (board[i][j] == ' '){
                int score = magic[i][j];
                if (score > bestscore){
                    bestscore = score;
                    row = i;
                    col = j;
                }
            }
        }
    }
    board[row][col] = 'O';
}

int main(){
    char board[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}};
    // Human (1) - 'X', AI - 'O'
    int turn = 1;
    while(1){
        printboard(board);
        if (turn == 1){
            int move;
            printf("Enter Move 1-9:");
            scanf("%d", &move);
            int row = (move - 1) / 3;
            int col = (move - 1) % 3;
            if (board[row][col] == ' '){
                board[row][col] = 'X';
            }
            else{
                printf("Inavalid move \n");
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
            printf("You win! \n");
            break;
        }
        else if (checkwin(board, 'O')){
            printboard(board);
            printf("Computer wins! \n");
            break;
        }
        else if (isfull(board)){
            printboard(board);
            printf("Its a draw \n");
            break;
        }
    }
}