#include<iostream>
#include<vector>
#include<string>
#include"Parser.hpp"
#include"SatSolver.hpp"
using namespace std;

SatSolver solver;

int main(int argc, char* argv[]){
    
    /* check input file */
    if ( argc < 2 ){
        cerr << "EXECUTION COMMAND> \"/(EXEC_FILE) (CNF_FILE)\"" << endl;
        return 1;
    } 
    solver.LoadCNF(argv[1]);
    solver.ShowCNF();

    solver.DavisPutman();
    solver.DavisPutman();
    solver.DavisPutman();
    return 0;
}

