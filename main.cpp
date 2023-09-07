#include <iostream>
#include <vector>
using namespace std;

// Simple Cell Struct used to hold a probability, previous state, and current state
struct Cell{
    long double p;
    int prev;
    int curr;
    Cell(){
        p = 0.0;
        prev = -1;
        curr = -1;
    }
};

// Simple HMM Struct that holds initial probabilities for states, transition table, emission table
//  as well as num of states and num of possible observations
struct HMM{ 
    vector<long double> jp_init;
    vector<vector<long double>> transition_table;
    vector<vector<long double>> emmission_table;
    int num_states;
    int num_possible_observations;
    HMM(vector<long double> x, vector<vector<long double>> y, vector<vector<long double>> z){
        jp_init = x;
        transition_table = y;
        emmission_table = z;
        num_states = jp_init.size();
        num_possible_observations = emmission_table.front().size();
    }
};
/*
Purpose: Run Viterbi's Algorithm on a HMM given a set of observations represented as integers
Input Parameters: HMM object, vector of observations represented as integers, boolean flag representing whether the entire Markov Chain should be printed
Output Parameters: None
Return Value: Vector of ints representing most probable path travelled
*/
vector<int> viterbiPath(const HMM &h, vector<int> obs, bool printM){
    // create matrix of Cell objects to hold probs of paths endings at v[i][j]
    vector<vector<Cell>> v (h.num_states, vector<Cell> (obs.size()));
    for (int i = 0; i < h.num_states; i++){ // for each state in v, find joint probs of current state at time 0 and first observation
        v[i][0].p = h.jp_init[i] * h.emmission_table[i][obs[0]];
        v[i][0].curr = i;
    }
    for (uint i = 1; i < obs.size(); i++){ // for each observation, starting at 2nd
        for (int j = 0; j < h.num_states; j++){ // for each state in HMM
            // calculate prob of going from  state at previous observation to next state given current observation
            long double max = 0;
            v[j][i].prev = 0;
            v[j][i].curr = j;
            for (int p = 0; p < h.num_states; p++){ // pth states to compare
                long double temp = v[p][i-1].p * h.transition_table[p][j] * h.emmission_table[j][obs[i]];
                if (max < temp){ // if a new max was found, update
                    max = temp;
                    v[j][i].prev = p;
                }
            }
            v[j][i].p = max; // max to state j at observation has been found
        }
    }
    if (printM){ // if we should print the matrix V's contents
        for (uint i = 0; i < v.size(); i++){
            for (uint j = 0; j < v.front().size(); j++){
                cout << v[i][j].p << " ";
            }
            cout << endl;
        }
        cout << endl;
    }
    int row = 0;
    for (uint i = 1; i < v.size(); i++){ // find most likely path from maximum final state probability
        if (v[row][v.front().size() - 1].p < v[i][v.front().size() - 1].p){
            row = i;
        }
    }
    vector<int> result (obs.size()); // path to return
    int column = v.front().size() - 1; // start at last observation
    for (int i = obs.size() - 1; i >= 0; i--){ // build path backwards
        result.at(i) = v[row][column].curr;
        row = v[row][column].prev; // update next state in path
        column--; // change observations
    } 
    return result;
}
/*
Purpose: Main entry point of program. Grabs input from user to build a HMM and get a set of observations to test.
Input Parameters: None
Output Parameters: None
Return: 0 on success 
*/
int main(){
    int num_states;
    cin >> num_states; // get num of states of HMM
    vector<long double> initial_p;
    long double prob = 0.0;
    for (int i = 0; i < num_states; i++){ // get initial probs at timestate 0
        cin >> prob;
        initial_p.push_back(prob);
    }
    vector<vector<long double>> transition_table (num_states, vector<long double> (num_states, 0.0)); // build transition table
    for (uint i = 0; i < transition_table.size(); i++){ // from each state
        for (uint j = 0; j < transition_table.size(); j++){  // to each state
            cin >> prob;
            transition_table[i][j] = prob;
        }
    }
    int num_possible_observations; // how many observations from states can be seen
    cin >> num_possible_observations;
    vector<vector<long double>> emmission_table(num_states, vector<long double> (num_possible_observations, 0.0)); // build emmission table 
    for (int i = 0; i < num_states; i++){ // from each state
        for (int j = 0; j < num_possible_observations; j++){ // to each possible observation
            cin >> prob;
            emmission_table[i][j] = prob;
        }
    }
    int observations; // have observations have been recorded
    cin >> observations;
    vector<int> observed (observations);
    int x;
    for (int i = 0; i < observations; i++){ // grab individual recorded observations from user
        cin >> x;
        observed[i] = x;
    }
    HMM h(initial_p, transition_table, emmission_table); // create HMM
    bool print = true; // print matrix table in viterbiPath
    vector <int> result = viterbiPath(h, observed, print); // run Viterbi's algorithm, store viterbi path into result
    for (uint i = 0; i < result.size(); i++){ // print path
        cout << result[i] << " ";
    }
    cout << endl;
    return 0;
}
