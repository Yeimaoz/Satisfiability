#pragma once
#include <vector>
#include "Parser.hpp"
#include <cmath>
#include <algorithm>
using std::vector;

typedef vector<int> CLAUSE;

class SatSolver {

    private:
        vector<CLAUSE> clauses;       
        vector<CLAUSE> update;       
        int maxVarIndex;

    public:
        void LoadCNF(char*);
        void DavisPutman();
        void SortVariable(CLAUSE&);
        void SortClause();
        void ReduceClause();

        void ShowCNF();
        void ShowClause(CLAUSE&);

        CLAUSE Combine(CLAUSE&,CLAUSE&);
        
};
