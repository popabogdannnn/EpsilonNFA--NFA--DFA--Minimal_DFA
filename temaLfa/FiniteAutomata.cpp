#include "FiniteAutomata.h"

FiniteAutomata::FiniteAutomata(int _numOfStates, int _startingState, vector <int>& _finalStates) :
    numOfStates(_numOfStates), startingState(_startingState)
{
    for (auto it : _finalStates) {
        finalStates.insert(it);
    }
}

FiniteAutomata::FiniteAutomata()
{
    //cout << 1;
}


