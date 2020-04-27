#pragma once
#include <vector>
#include <tuple>
#include <cstring>
#include <algorithm>
#include <queue>
#include <set>
#include <string>
#include <iostream>
#include "Transition.h"

using namespace std;

class FiniteAutomata /// = (numOfStates, startingState, finalStates, transition, alphabet)
{
protected:
    set <int> finalStates;
    int startingState;
    int numOfStates;
    set < pair <int, int> > visited;

public:
    FiniteAutomata(int, int, vector <int>&);
    FiniteAutomata();

    virtual bool accepts(string& S) = 0;

};
