#pragma once
#include "FiniteAutomata.h"
#include "NFA.h"


class LambdaNFA : public FiniteAutomata
{
private:
    vector < vector <int> > T[30]; /// T[ch][i] = the list of the neighbour states going from state i with char ch (which can be lambda)

    bool DFS(int currentState, int index, string& S);

public:
    LambdaNFA(int, int, vector <int>&, vector < Transition>&, char lambda);

    NFA turnIntoNFA();

    bool accepts(string& S);
};


