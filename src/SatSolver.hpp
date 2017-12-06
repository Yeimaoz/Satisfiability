#pragma once
#include <vector>
#include "Parser.hpp"
using std::vector;

class SatSolver {
    typedef vector<int> CLAUSE;

    private:
        vector<CLAUSE> clauses;       
        int maxVarIndex;

    public:
        void LoadCNF(char*);
        void ShowCNF();
};
