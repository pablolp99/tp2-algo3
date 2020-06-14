#include <iostream>
#include "graphs.h"
#include "unionfind.h"
#include <vector>


int main() {
    Graph g = readGraph();
    Graph h = shortestEdge(g);
    return 0;
}
