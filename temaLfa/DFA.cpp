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

bool DFA::accepts(string& S)
{
    return DFS(startingState, 0, S);
}
