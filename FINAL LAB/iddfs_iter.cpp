#include <iostream>
#include <stack>
#include <unordered_set>
#include <vector>
using namespace std;

const int N = 3; // Size of puzzle

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

vector<State> getSuccessors(State state) {
    vector<State> successors;
    // Possible moves: Left, Right, Up, Down 
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++) {
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

bool iddfs(State start_state, State goal_state, int max_depth,int& states_explored){
    for(int depth_limit = 0; depth_limit <= max_depth; ++depth_limit){
        stack<State> s;
        unordered_set<int> visited;
        s.push(start_state);
        int start_hash = 0;
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                start_hash = start_hash * 10 + start_state.puzzle[i][j];
            }
        }
        visited.insert(start_hash);

        while (!s.empty()) {
            State current = s.top();
            s.pop();
            states_explored++;

            if (current.depth > depth_limit)
                continue;

            if (is_goal_state(current, goal_state)) {
                print_puzzle(current);
                cout << endl;
                cout << "Goal state found at depth: " << current.depth << endl;
                return true;
            }

            vector<State> successors = getSuccessors(current);
            for (State successor : successors) {
                int hash_value = 0;
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        hash_value = hash_value * 10 + successor.puzzle[i][j];
                    }
                }
                if (!visited.count(hash_value)) {
                    s.push(successor);
                    visited.insert(hash_value);
                }
            }
        }
        
    }
    return false;
}

int main() {
    //ITERATIVE DEEPINING DEPTH FIRST 
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
         {7, 8, 0}},
        2, 2, // position of zero (empty tile)
    };

    int max_depth = 4; // Maximum depth to search
    
    int states_explored = 0;

    if (!iddfs(start_state, goal_state, max_depth, states_explored)) {
        cout << "Goal state not found within depth limit." << endl;
    }
    
    cout << "States explored: " << states_explored << endl;
    return 0;
}
