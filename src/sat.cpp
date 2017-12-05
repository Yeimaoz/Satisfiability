#include<iostream>
#include<vector>
#include<string>
#include"parser.hpp"
using namespace std;

int maxVarIndex;
vector<vector<int>> clauses;
string filename;

int main(int argc, char* argv[]){
    if ( argc < 2 ){
        cerr << "EXECUTION COMMAND> \"/(EXEC_FILE) (CNF_FILE)\"" << endl;
        return 1;
    } 
    filename = argv[1];
    parse_DIMACS_CNF(clauses,maxVarIndex,filename.c_str());
    
    for ( auto& clause : clauses ){
        cout << "CLAUSE: ";
        for ( auto var : clause )
            cout << var << " ";
        cout << endl;
    }

    return 0;
}
