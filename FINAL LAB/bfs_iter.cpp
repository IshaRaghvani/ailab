#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>
using namespace std;

const int N = 3; // size of puzzle

struct State {
    int puzzle[N][N];
    int zero_i, zero_j; // position of the zero (empty tile)
    int depth; // depth of the state
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

bool is_valid(int i, int j){
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

int bfs(State start_state, State goal_state) {
    queue<State> q;
    unordered_set<int> visited;
    q.push(start_state);
    int start_hash = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            start_hash = start_hash * 10 + start_state.puzzle[i][j];
        }
    }
    visited.insert(start_hash);
    int states_visited = 1; 

    while (!q.empty()) {
        int level_size = q.size();
        for (int i = 0; i < level_size; ++i) {
            State current = q.front();
            q.pop();
            if (is_goal_state(current, goal_state)) {
                cout << "===== Goal State Found at depth " << current.depth << " ========" << endl;
                print_puzzle(current);
                cout << endl;
                return states_visited;
            }
            vector<State> successors = get_successors(current);
            for (State successor : successors) {
                int hash_value = 0;
                for (int i = 0; i < N; ++i) {
                    for (int j = 0; j < N; ++j) {
                        hash_value = hash_value * 10 + successor.puzzle[i][j];
                    }
                }
                if (!visited.count(hash_value)) {
                    q.push(successor);
                    visited.insert(hash_value);
                    states_visited++;
                }
            }
        }
    }
    cout << "Goal state not reachable\n";
    return states_visited; 
}


int main() {
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
    int num_states_visited = bfs(start_state, goal_state);
    cout << "Number of states visited in BFS: " << num_states_visited << endl;
    return 0;
}
