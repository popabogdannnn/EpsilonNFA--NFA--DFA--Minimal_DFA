#pragma once

#include "FiniteAutomata.h"
#include "DFA.h"

class NFA : public FiniteAutomata
{
private:
    vector < vector <int> > T[30]; /// T[ch][i] = the list of the neighbour states going from state i with char ch

    bool DFS(int currentState, int index, string& S);

public:
    NFA(int, int, vector <int>&, vector <tuple <int, char, int> >&);
    NFA();

    DFA turnIntoDFA();

    bool accepts(string& S);
};


