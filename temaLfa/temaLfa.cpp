#include <iostream>
#include <fstream>
#include "LambdaNFA.h"


using namespace std;

/*
    Input format:
    First line: N - number of states, M - number of transitions
    states are from set {0, 1, 2, ..., N - 1}
    Next M lines: x y c  transition from x to y through c (any non alpha char will be treated as lambda)
    Next line - q0 initial state
    Next line - F - number of final states
    Next line - F numbers representing final states

*/





ifstream fin("data.in");

vector < Transition > T;
vector <int> finalStates;
int N, M;


int main()
{
    fin >> N >> M;
    
    while (M--) {
        int x, y;
        char c;
        fin >> x >> y >> c;
        if (!(c >= 'a' && c <= 'z')) {
            c = '$';
        }

        T.push_back(Transition(x, c, y));
    }

    int q0;
    fin >> q0;

    int F;
    fin >> F;
    for (int i = 1; i <= F; i++) {
        int x;
        fin >> x;
        finalStates.push_back(x);
    }

 

    LambdaNFA QL(N, q0, finalStates, T, '$');
    string check("abc");

    cout << QL.accepts(check);

    NFA QNFA = QL.turnIntoNFA();

    cout << QNFA.accepts(check);

    DFA QDFA = QNFA.turnIntoDFA();

    cout << QDFA.accepts(check);

    DFA minimalDFA = QDFA.minimize();

    cout << minimalDFA.accepts(check);
   
    return 0;
}
