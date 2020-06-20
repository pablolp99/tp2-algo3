#include "algorithms.h"
#include <iostream>
#include "graphs.h"
#include "unionfind.h"
#include <vector>


int main() {
    ALGraph g = readALGraph();
    heurisitcAgm(g);
//    heurisitcAgm(g);
    return 0;
}

//4 6
//1 2 50
//1 3 40
//1 4 10
//2 3 20
//2 4 30
//3 4 15

//6 15
//1 2 2
//1 3 3
//1 4 3
//1 5 1
//1 6 4
//2 3 3
//2 4 3
//2 5 3
//2 6 3
//3 4 5
//3 5 4
//3 6 5
//4 5 2
//4 6 2
//5 6 3