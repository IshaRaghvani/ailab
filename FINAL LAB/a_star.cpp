#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_set>
#include <queue>
using namespace std;

const int N = 3;
struct State{
    int puzzle[N][N];
    int zero_i, zero_j;
    int depth;
    int heuristic;
};

bool goalstate(State initial_state, State goal_state){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (initial_state.puzzle[i][j] != goal_state.puzzle[i][j])
            {
                return false;
            }
        }
    }
    return true;
}

bool isValid(int i, int j){
    return i >= 0 && j >= 0 && i < N && j < N;
}

struct CompareStates{
    bool operator()(State a, State b){
        return a.heuristic + a.depth > b.heuristic + b.depth;
    }
};

int heuristic(int puzzle[N][N], State goal_state){
    int h = 0;
    // Manhattan Distance for differences of tile positions
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++){
            if (puzzle[i][j] != 0){
                // Find similar tile in goal state
                for (int goal_i = 0; goal_i < N; goal_i++){
                    for (int goal_j = 0; goal_j < N; goal_j++){
                        if (goal_state.puzzle[goal_i][goal_j] == puzzle[i][j]){
                            h += abs(goal_i - i) + abs(goal_j - j);
                        }
                    }
                }
            }
        } 
    }
    return h;
}

vector<State> get_successors(State state, State goal_state){
    vector<State> successors;
    // Possible moves: Left, Right, Up, Down
    int di[] = {-1, 1, 0, 0};
    int dj[] = {0, 0, -1, 1};
    for (int d = 0; d < 4; d++){
        int ni = state.zero_i + di[d];
        int nj = state.zero_j + dj[d];
        if (isValid(ni, nj)){
            State successor = state;
            swap(successor.puzzle[state.zero_i][state.zero_j], successor.puzzle[ni][nj]);
            successor.zero_i = ni;
            successor.zero_j = nj;
            successor.depth = state.depth + 1;
            successor.heuristic = heuristic(successor.puzzle, goal_state);
            successors.push_back(successor);
        }
    }
    return successors;
}

int aStar(State initial_state, State goal_state){
    // Create Min Heap
    // State - Type of elements to store
    // vector<State> - Type of internal container used to store these elements
    // CompareStates - Custom comparison function tyo order within the priority queue
    priority_queue<State, vector<State>, CompareStates> pq;
    unordered_set<int> visited;
    pq.push(initial_state);
    int start_hash = 0;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            start_hash = start_hash * 10 + initial_state.puzzle[i][j];
        }
    }
    visited.insert(start_hash);
    int count = 1;

    while (!pq.empty()){
        State current = pq.top();
        pq.pop();
        if (goalstate(current, goal_state)){
            cout << "Solution found" << endl;
            return count;
        }
        vector<State> successors = get_successors(current, goal_state);
        for (State successor : successors){
            int hashval = 0;
            for (int i = 0; i < N; i++){
                for (int j = 0; j < N; j++){
                    hashval = hashval * 10 + successor.puzzle[i][j];
                }
            }
            if (!visited.count(hashval)){
                pq.push(successor);
                visited.insert(hashval);
                count++;
            }
        }
    }
    return count;
}

int main(){
    State start_state = {
        {{1, 2, 3},
         {0, 4, 6},
         {7, 5, 8}},
        1,0,
        0};
    State goal_state = {
        {{1, 2, 3},
        {4, 5, 6},
        {7, 8, 0}},
        2, 2,
        0 // Goal state provided in main function
    };
    int count = aStar(start_state, goal_state);
    cout << "Number of states visited: " << count << endl;
    return 0;
}