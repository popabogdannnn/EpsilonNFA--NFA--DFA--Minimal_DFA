#include "DFA.h"

///private functions

bool DFA::DFS(int currentState, int index, string& S)
{
    if (index == S.size()) {
        return finalStates.find(currentState) != finalStates.end();
    }

    if (T[S[index] - 'a'][currentState] != -1) {
        return DFS(T[S[index] - 'a'][currentState], index + 1, S);
    }

    return false;
}

void DFA::KEEP(int currentState, vector<int>& keep)
{
    if (keep[currentState] != 0) {
        return;
    }

    keep[currentState] = 1;

    if (finalStates.find(currentState) != finalStates.end()) {
        keep[currentState] = 2;
    }

    for (int ch = 0; ch < 26; ch++) {
        if (T[ch][currentState] != -1) {
            KEEP(T[ch][currentState], keep);
            if (keep[T[ch][currentState]] == 2) {
                keep[currentState] = 2;
            }
        }
    }
}


///public functions

DFA::DFA(int _numOfStates, int _startingState, vector <int>& _finalStates, vector <tuple <int, char, int> >& transitions) :
    FiniteAutomata(_numOfStates, _startingState, _finalStates)
{
    for (int ch = 0; ch < 26; ch++) {
        T[ch].resize(_numOfStates, -1);
    }

    for (auto it : transitions) {
        int xx = get<0>(it);
        int ch = get<1>(it) - 'a';
        int yy = get<2>(it);
        if (T[ch][xx] != -1) {
            cout << "DIDN'T GET A DFA\n";
        }
        T[ch][xx] = yy;
    }
}

DFA::DFA()
{
}

DFA DFA::minimize()
{
    vector <int> prev(numOfStates, 0);

    for (int i = 0; i < numOfStates; i++) {
        if (finalStates.find(i) != finalStates.end()) {
            prev[i] = 1;
        }
    }


   

    int prevCnt = 2;

    while (1) {
        vector <int> curr(numOfStates, -1);
        int currCnt = 0;

        for (int i = 0; i < numOfStates; i++) {
            if (curr[i] == -1) {
                curr[i] = currCnt++;
                for (int j = i + 1; j < numOfStates; j++) {
                    if (prev[i] == prev[j]) {
                        bool ok = true;
                        for (int ch = 0; ch < 26; ch++) {
                            if (T[ch][i] == -1 && T[ch][j] == -1) {

                            }
                            else if (T[ch][i] != -1 && T[ch][j] != -1) {
                                if (prev[T[ch][i]] != prev[T[ch][j]]) {
                                    ok = false;
                                }
                            }
                            else {
                                
                                ok = false;
                            }
                        }
                        
                        if (ok) {
                            curr[j] = curr[i];
                        }

                    }
                }
            }
        }

        if (prevCnt == currCnt) {
            break;
        }

        prevCnt = currCnt;
        prev = curr;
    }
    
    vector <int> keep(numOfStates, 0);
    KEEP(startingState, keep);
    
    vector <int> mp(numOfStates, -1);
    int newNumOfStates = 0;
    int newStartingState = 0;

    for (int i = 0; i < numOfStates; i++) {
        if (keep[i] == 2 && mp[prev[i]] == -1) {
            mp[prev[i]] = newNumOfStates++;
        }
    }

    newStartingState = mp[prev[startingState]];
    set < tuple <int, char, int> > transitionSet;

    for (int i = 0; i < numOfStates; i++) {
        if (mp[i] != -1) {
            for (char ch = 0; ch < 26; ch++) {
                if (T[ch][i] != -1) {
                    if (mp[T[ch][i]] != -1) {
                        transitionSet.insert(make_tuple(mp[i], char(ch + 'a'), mp[T[ch][i]]));
                    }
                }
            }
        }
    }

   // cout << "\n";
   // cout << newNumOfStates << " " << newStartingState << "\n";

    vector <tuple <int, char, int>> newTransitions;
    for (auto it : transitionSet) {
        newTransitions.push_back(it);
        //cout << get<0>(it) << " " << get<1>(it) << " " << get<2>(it) << "\n";
    }

    vector <int> newFinalStates;

    for (int i = 0; i < numOfStates; i++) {
        if (finalStates.find(i) != finalStates.end()) {
            newFinalStates.push_back(mp[i]);
        }
    }
    return DFA(newNumOfStates, newStartingState, newFinalStates, newTransitions);
}

bool DFA::accepts(string& S)
{
    return DFS(startingState, 0, S);
}
