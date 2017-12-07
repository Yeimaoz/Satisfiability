#include <iostream>
#include "SatSolver.hpp"
using std::cout;
using std::cin;
using std::endl;

void SatSolver::LoadCNF(char* filename){
    /* use the cnf parser api to parse the cnf file */
    parse_DIMACS_CNF(clauses,maxVarIndex,filename);

}

void SatSolver::DavisPutman(){
    update.resize(0);
    const size_t oriClauseCount = clauses.size(); 
    vector<bool> usedClause(oriClauseCount, false);
    for ( size_t i = 0; i < oriClauseCount ; ++i ){
        for ( size_t j = 0 ; j < oriClauseCount ; ++j ){
            if ( clauses[i] != clauses[j] ){
                CLAUSE temp;
                bool completed = false;
                for ( size_t m = 0; m < clauses[i].size(); ++m ){
                    for ( size_t n = 0 ; n < clauses[j].size(); ++n ){
                        if ( !(clauses[i][m]+clauses[j][n]) ){
                            temp = Combine(clauses[i],clauses[j]);
                            usedClause[i] = true;
                            usedClause[j] = true;
                            completed = true;
                            break;
                        }
                    }    
                    if ( completed )
                        break;
                }       
                if ( !temp.empty() )
                    update.push_back(temp);
            }
        }
    }
    for ( size_t i = 0; i < clauses.size(); ++i ){
        if ( !usedClause[i] )
            update.push_back(clauses[i]);
    }
    if ( update.size() > 1 )
        SortClause();
    ReduceClause();
    ShowCNF();
}

CLAUSE SatSolver::Combine(CLAUSE& c1, CLAUSE& c2){
    vector<bool> used1(c1.size(),false);
    vector<bool> used2(c2.size(),false);
    CLAUSE result;

    // mark the elimiated variable
    for ( size_t m = 0; m < c1.size(); ++m ){
        for ( size_t n = 0 ; n < c2.size(); ++n ){
            if ( !(c1[m]+c2[n]) ){
                used1[m] = true;
                used2[n] = true;
            }
        }    
    }       

    // collect the unused variable
    for ( size_t m = 0; m < c1.size(); ++m )
        if ( !used1[m] )
            result.push_back(c1[m]);
    for ( size_t m = 0; m < c2.size(); ++m )
        if ( !used2[m] ){
            bool exist = false;
            for ( size_t i = 0 ; i < result.size(); ++i ){
                if ( c2[m] == result[i] ){
                    exist = true;
                    break;
                }
            }
            if ( !exist )
                result.push_back(c2[m]);

        }
    if ( result.size() > 1 )
        SortVariable(result);
    return result; 
}

void SatSolver::ShowCNF(){
    cout << "[CNF's maxVarIndex]: " << maxVarIndex << endl;
    for ( size_t i = 0 ; i < clauses.size() ; ++i ){
        cout << "[CLAUSE " << i << "]: ";
        for ( size_t j = 0 ; j < clauses[i].size() ; ++j )
            cout << clauses[i][j] << " ";
        cout << endl;
    }
}

void SatSolver::ShowClause(CLAUSE& in){
    cout << "[CLAUSE]: ";
    for ( size_t j = 0 ; j < in.size() ; ++j )
        cout << in[j] << " ";
    cout << endl;
}

void SatSolver::SortVariable(CLAUSE& in){
    std::sort(in.begin(), in.end(),[](const int lhs, const int rhs) {
            return abs(lhs) < abs(rhs);
            });
}

void SatSolver::SortClause(){
    std::sort( 
        update.begin(), 
        update.end(),
        [](const CLAUSE& lhs, const CLAUSE& rhs) {
            if ( lhs.size() < rhs.size() )
                return true;
            else if ( lhs.size() == rhs.size() ){
                    
                for ( size_t i = 0 ; i < lhs.size() ; ++i ) {
                    if ( lhs[i] == rhs[i] )
                        return true;
                }
                for ( size_t i = 0 ; i < lhs.size() ; ++i ){
                    if ( abs(lhs[i]) < abs(rhs[i]) )
                        return true;
                }                
            }
            return false;
        }
    );
}

void SatSolver::ReduceClause(){
    vector<CLAUSE> temp;
    if ( update.size() > 1 ){
        temp.push_back(update.front());
        for ( size_t i = 0 ; i < update.size(); ++i ){
            if ( update[i] != temp.back() )
                temp.push_back(update[i]);
        }
    }
    clauses = temp;
}
