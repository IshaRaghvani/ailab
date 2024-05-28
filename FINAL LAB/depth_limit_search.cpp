#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

const int N = 3;
struct State {
    int puzzle[N][N];
    int zero_i, zero_j;
    int depth;
};

bool goalState(State state, State goal_state) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (state.puzzle[i][j] != goal_state.puzzle[i][j]) {
                return false;
            }
        }
    }
    return true;
}

bool isValid(int i, int j) {
    return i >= 0 && j >= 0 && i < N && j < N;
}

vector<State> getSuccessors(State state) {
    vector<State> successors;
    // Possible moves: Left, Right, Up, Down 
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
        int ni = state.zero_i + di[d];
        int nj = state.zero_j + dj[d];
        if (isValid(ni, nj)) {
            State successor = state;
            swap(successor.puzzle[state.zero_i][state.zero_j], successor.puzzle[ni][nj]);
            successor.zero_i = ni;
            successor.zero_j = nj;
            successor.depth = state.depth + 1;
            successors.push_back(successor);
        }
    }
    return successors;
}

bool depthLimitedSearch(State current, State goal_state, int limit) 
{

    if (goalState(current, goal_state)) {
        return true;
    }
    if (current.depth >= limit) {
        return false;
    }
    vector<State> successors = getSuccessors(current);
    for (const State &successor : successors) {
        if (depthLimitedSearch(successor, goal_state, limit)) {
            return true;
        }
    }
    return false;
}

void printPuzzle(const int puzzle[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    //DEPTH LIMIT SEARCH
    State start_state = {
        {{1, 2, 3},
         {0, 4, 6},
         {7, 5, 8}},
        1, 0, // pos on empty box
        0
    }; //initial depth
    State goal_state = {
        {{1, 2, 3},
         {4, 5, 6},
         {7, 8, 0}},
        2, 2, 
        0
    };

    int depth_limit = 3;
    if (depthLimitedSearch(start_state, goal_state, depth_limit)) {
        cout << "Solution found within depth limit!" << endl;
    } else {
        cout << "No solution found within depth limit." << endl;
    }
    return 0;
}
