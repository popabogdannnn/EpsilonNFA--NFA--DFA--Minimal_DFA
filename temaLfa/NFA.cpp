#include "NFA.h"

///private functions

bool NFA::DFS(int currentState, int index, string& S)
{
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

    return false;
}

///public functions

NFA::NFA(int _numOfStates, int _startingState, vector <int>& _finalStates, vector <tuple <int, char, int> >& transitions) :
    FiniteAutomata(_numOfStates, _startingState, _finalStates)
{
    for (int ch = 0; ch < 26; ch++) {
        T[ch].resize(_numOfStates);
    }

    for (auto it : transitions) {
        int xx = get<0>(it);
        int ch = get<1>(it) - 'a';
        int yy = get<2>(it);
        T[ch][xx].push_back(yy);
    }
}

NFA::NFA()
{

}


bool NFA::accepts(string& S)
{
    bool ret = DFS(startingState, 0, S);
    visited.clear();
    return ret;
}

bool operator == (const set<int>& a, const set <int>& b)
{
    if (a.size() != b.size()) {
        return false;
    }

    for (auto it : a) {
        if (b.find(it) == b.end()) {
            return false;
        }
    }

    return true;
}

DFA NFA::turnIntoDFA()
{
    queue < set <int> > Q;
    set <int> start;
    start.insert(startingState);
    Q.push(start);

    int newNumOfStates = 1;
    vector< set <int> > newStates;
    newStates.push_back(start);
    vector <int> newFinalStates;
    int newStartingState = 0;
    vector <tuple <int, char, int> > newTransitions;

    if (finalStates.find(startingState) != finalStates.end()) {
        newFinalStates.push_back(0);
    }

    while (!Q.empty()) {
        set <int> currentSet = Q.front();
        Q.pop();
        int currentState = find(newStates.begin(), newStates.end(), currentSet) - newStates.begin();

        for (int ch = 0; ch < 26; ch++) {
            set <int> nextSet;
            bool isFinal = false;

            for (auto inSet : currentSet) {
                for (auto neigh : T[ch][inSet]) {
                    nextSet.insert(neigh);
                    if (finalStates.find(neigh) != finalStates.end()) {
                        isFinal = true;
                    }
                }
            }

            if (!nextSet.empty()) {

                if (find(newStates.begin(), newStates.end(), nextSet) == newStates.end()) {
                    newStates.push_back(nextSet);
                    newFinalStates.push_back(newNumOfStates);
                    newNumOfStates++;
                    Q.push(nextSet);
                }

                int nextState = find(newStates.begin(), newStates.end(), nextSet) - newStates.begin();

                newTransitions.push_back(make_tuple(currentState, ch + 'a', nextState));
            }
        }
    }

    return DFA(newNumOfStates, newStartingState, newFinalStates, newTransitions);
}
