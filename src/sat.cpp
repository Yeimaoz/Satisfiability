#include<iostream>
#include<vector>
#include<string>
#include"parser.hpp"
using namespace std;

int maxVarIndex;
vector<vector<int>> clauses;
string filename;

void printCNF();

int main(int argc, char* argv[]){
    
    /* check input file */
    if ( argc < 2 ){
        cerr << "EXECUTION COMMAND> \"/(EXEC_FILE) (CNF_FILE)\"" << endl;
        return 1;
    } 

    filename = argv[1];

    /* use the cnf parser api to parse the cnf file */
    parse_DIMACS_CNF(clauses,maxVarIndex,filename.c_str());
    
    printCNF();

    return 0;
}

void printCNF(){
    cout << "[CNF's information]: " << endl;
    for ( size_t i = 0 ; i < clauses.size() ; ++i ){
        cout << "[CLAUSE " << i << "]: ";
        for ( size_t j = 0 ; j < clauses[i].size() ; ++j )
            cout << clauses[i][j] << " ";
        cout << endl;
    }
    
}
