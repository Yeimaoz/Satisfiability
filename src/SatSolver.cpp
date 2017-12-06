#include <iostream>
#include "SatSolver.hpp"
using std::cout;
using std::cin;
using std::endl;

void SatSolver::LoadCNF(char* filename){
    /* use the cnf parser api to parse the cnf file */
    parse_DIMACS_CNF(clauses,maxVarIndex,filename);
    
}

void SatSolver::ShowCNF(){
    cout << "[CNF's information]: " << endl;
    for ( size_t i = 0 ; i < clauses.size() ; ++i ){
        cout << "[CLAUSE " << i << "]: ";
        for ( size_t j = 0 ; j < clauses[i].size() ; ++j )
            cout << clauses[i][j] << " ";
        cout << endl;
    }
    
}
