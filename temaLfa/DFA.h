#pragma once

#include "FiniteAutomata.h"


class DFA : public FiniteAutomata
{

private:

    vector <int> T[30];
    bool DFS(int currentState, int index, string& S);
    void KEEP(int currentState, vector <int>& keep);

public:

    DFA(int, int, vector <int>&, vector <tuple <int, char, int> >&);
    DFA();

    DFA minimize();
    bool accepts(string& S);

};

