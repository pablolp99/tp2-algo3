#include "algorithms.h"
#include <iostream>
#include "graphs.h"
#include "unionfind.h"
#include <vector>
#include <ctime>

#define MEM_SIZE 2000
#define ASPIRATION_STALL 180
#define MAX_ITERATIONS 10000
#define MAX_VECINITY_SIZE 100
#define TERMINATION_CONDITION 500


int main() {
    srand(time(NULL));
    ALGraph g = readALGraph();
//    shortestEdge(g);
//    heuristicAGM(g);
    ALGraph cycle = tabuSearchExplored(g, shortestEdge, MEM_SIZE, MAX_VECINITY_SIZE, ASPIRATION_STALL, TERMINATION_CONDITION, MAX_ITERATIONS);
    bool isAMotherFuckingCycle = cycle.isCycle();
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