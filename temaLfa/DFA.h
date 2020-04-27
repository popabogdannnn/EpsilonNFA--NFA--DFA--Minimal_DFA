#pragma once

#include "FiniteAutomata.h"


class DFA : public FiniteAutomata
{

private:

    vector <int> T[30];
    bool DFS(int currentState, int index, string& S);

public:

    DFA(int, int, vector <int>&, vector <tuple <int, char, int> >&);
    bool accepts(string& S);

};

