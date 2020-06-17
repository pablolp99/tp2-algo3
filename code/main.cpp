#include <iostream>
#include "graphs.h"
#include "unionfind.h"
#include <vector>


int main() {
//    Graph g = readGraph();
//    vector<Edge> e = shortestEdge(g);
    ALGraph g = readALGraph();
    ALGraph prim = primMST(g);
    dfs(prim);
//    vector<int> res = nearestNeighbour(g);
    return 0;
}

