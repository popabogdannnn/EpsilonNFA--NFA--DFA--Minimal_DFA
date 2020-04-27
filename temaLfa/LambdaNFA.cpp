#include "LambdaNFA.h"

///private functions

bool LambdaNFA::DFS(int currentState, int index, string& S)
{
    //cout << currentState << "\n";
    if (index == S.size()) {
        return finalStates.find(currentState) != finalStates.end();
    }

    if (visited.find(make_pair(currentState, index)) != visited.end()) {
        return false;
    }

    visited.insert(make_pair(currentState, index));

 

    for (auto it : T[S[index] - 'a'][currentState]) {
        if (DFS(it, index + 1, S)) {
            return true;
        }
    }

    for (auto it : T[26][currentState]) {
        if (DFS(it, index, S)) {
            return true;
        }
    }

    return false;
}

///public functions

LambdaNFA::LambdaNFA(int _numOfStates, int _startingState, vector <int>& _finalStates, vector < Transition >& transitions, char lambda) :
    FiniteAutomata(_numOfStates, _startingState, _finalStates)
{
    //cout << transitions.size();
    //while(1);
   // cout << numOfStates << "\n";
    for (int ch = 0; ch <= 26; ch++) {
        T[ch].resize(_numOfStates);
    }

    for (auto it : transitions) {
        int xx = it.x;
        char ch = it.c;
        int yy = it.y;
        if (ch == lambda) {
            ch = 26;
        }
        else {
            ch -= 'a';
        }
        T[ch][xx].push_back(yy);
    }
}

bool LambdaNFA::accepts(string& S)
{
   // cout << startingState << "\n";
    bool ret = DFS(startingState, 0, S);
    visited.clear();
    return ret;
}

NFA LambdaNFA::turnIntoNFA()
{
    vector< vector <bool> > LambdaTransition (numOfStates);

    for (int i = 0; i < numOfStates; i++) {
        LambdaTransition[i].resize(numOfStates);
    }

    for (int i = 0; i < numOfStates; i++) {
        for (auto it : T[26][i]) {
            LambdaTransition[i][it] = true;
        }
    }

    for (int k = 0; k < numOfStates; k++) { ///RoyFloyd for computing lambda-paths
        for (int i = 0; i < numOfStates; i++) {
            for (int j = 0; j < numOfStates; j++) {
                LambdaTransition[i][j] = LambdaTransition[i][j] || (LambdaTransition[i][k] && LambdaTransition[k][j]);
            }
        }
    }

    vector <tuple <int, char, int> > transitions;

    for (int i = 0; i < numOfStates; i++) { /// eliminating lambda transitions
        for (int j = 0; j < numOfStates; j++) {
            if (LambdaTransition[i][j]) {
                for (int ch = 0; ch < 26; ch++) {
                    for (auto it : T[ch][j]) {
                        transitions.push_back(make_tuple(i, ch + 'a', it));
                       // cout << i << " " << char(ch + 'a') << " " << it << "\n";
                    }
                }
            }
        }
    }

    for (int i = 0; i < numOfStates; i++) {
        for (int ch = 0; ch < 26; ch++) {
            for (auto it : T[ch][i]) {
                transitions.push_back(make_tuple(i, ch + 'a', it));
               // cout << i << " " << char(ch + 'a') << " " << it << "\n";
            }
        }
    }

    vector <int> fStates;
    for (auto it : finalStates) {
        fStates.push_back(it);
       // cout << it << " ";
    }
   //cout << "\n";

   // cout << numOfStates << " " << startingState << " ";
    
    //return NFA();
    return NFA(numOfStates, startingState, fStates, transitions);
}
