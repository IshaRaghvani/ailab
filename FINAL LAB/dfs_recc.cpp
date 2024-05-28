#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

const int N = 3; // size of puzzle

struct State {
    int puzzle[N][N];
    int zero_i, zero_j; // Position of the zero (empty tile)
    int depth; // Depth of the state
};

bool is_goal_state(State state, State goal_state) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            if (state.puzzle[i][j] != goal_state.puzzle[i][j]) {
                return false;
            }
        }
    }
    return true;
}

void print_puzzle(State state) {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << state.puzzle[i][j] << " ";
        }
        cout << endl;
    }
}

bool is_valid(int i, int j) {
    return i >= 0 && j >= 0 && i < N && j < N;
}

vector<State> get_successors(State state) {
    vector<State> successors;
    // Possible moves: Left, Right, Up, Down 
    int di[] = {-1, 1, 0, 0}; 
    int dj[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; ++d) {
        int ni = state.zero_i + di[d];
        int nj = state.zero_j + dj[d];
        if (is_valid(ni, nj)) {
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

bool dfs_recursion(State current, State goal_state, unordered_set<int>& visited) {
    if (is_goal_state(current, goal_state)) {
        return true;
    }
    int hash = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            hash = hash * 10 + current.puzzle[i][j];
        }
    }
    if (visited.count(hash)){
        return false;
    }
    visited.insert(hash);
    vector<State> successors = get_successors(current);
    for (State successor : successors) {
        if (dfs_recursion(successor, goal_state, visited)) {
                return true;
        }
    }
    return false;
}


int main() {
    // Depth-First Search (DFS)
    State start_state = {
        {{1, 2, 3},
        {0, 4, 6},
        {7, 5, 8}},
        1, 0, // position of zero (empty tile)
        0 // initial depth
    };
    State goal_state = {
        {{1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}}
    };
    unordered_set<int> visited;
    if(dfs_recursion(start_state, goal_state, visited)){
        cout << "Solution found." << endl;
    }
    else{
        cout << "No solution found." << endl;
    }
    return 0;
}