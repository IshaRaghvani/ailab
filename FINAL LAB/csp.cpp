#include <iostream>
#include <vector>
using namespace std;

const int N = 4; 

void print_board(vector<vector<int>>& board){
    // Print the solution
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j)
            cout << board[i][j] << " ";
        cout << endl;
    }
    cout << endl; 
}


bool isSafe(vector<vector<int>>& board, int row, int col) {
    // Queens in the same column
    for (int i = 0; i < row; ++i)
        if (board[i][col])
            return false;
    // Upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; --i, --j)
        if (board[i][j])
            return false;
    // Upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; --i, ++j)
        if (board[i][j])
            return false;
    return true;
}

void solveNQueens(vector<vector<int>>& board, int row) {
    if (row == N) { // All queens are placed
        print_board(board);
        return;
    }
    for (int col = 0; col < N; ++col) {
        if (isSafe(board, row, col)) {
            board[row][col] = 1; // Place the queen
            // Recur to place rest of the queens
            solveNQueens(board, row + 1);
            // Backtrack
            board[row][col] = 0;
        }
    }
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0)); // Initialize chessboard
    solveNQueens(board, 0);
    return 0;
}
