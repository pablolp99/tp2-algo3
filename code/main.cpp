#include <iostream>
#include "graphs.h"
#include "unionfind.h"
#include <vector>


int main() {
    ALGraph g = readALGraph();
    vector<int> res = nearestNeighbour(g);
    return 0;
}

