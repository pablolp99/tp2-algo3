#ifndef CODE_ALGORITHMS_H
#define CODE_ALGORITHMS_H

#include "graphs.h"
#include <vector>

#define UNDEFINED (-1)

struct Swap {
    Swap(Edge mEdge1, Edge mEdge2) : edge1(mEdge1), edge2(mEdge2) {};

    Edge edge1;
    Edge edge2;

    bool operator==(Swap other) {
        return edge1 == other.edge1 && edge2 == other.edge2;
    }
};

ALGraph readALGraph();

void closeCircuit(ALGraph g, vector<Edge> &sol, vector<Degree> deg);

ALGraph shortestEdge(ALGraph &g);

vector<int> minimumEdge(ALGraph &g, int &v, vector<bool> &flag);

ALGraph nearestNeighbour(ALGraph &g);

ALGraph kruskalMST(ALGraph g);

vector<int> DFS(ALGraph &g);

ALGraph heuristicAGM(ALGraph &g);

vector<pair<ALGraph, Swap>> getHeaviestEdgeSubVicinity(ALGraph &g, ALGraph &cycle, int vCount);

vector<pair<ALGraph, Swap>> getRandomSubVicinity(ALGraph &g, ALGraph &cycle, int vCount);

int findBestCycle(vector<pair<ALGraph, Swap>> &vicinity, vector<int> &memory, int vCount, bool flag, int &stopCond);

int findBestCycleWithSwapMemory(vector<pair<ALGraph, Swap>> &vicinity, vector<Swap> &memory, int vCount, bool flag, int &stopCond);

ALGraph tabuSearchWithExploredSolutionsMemory(ALGraph &g, ALGraph (*heuristic)(ALGraph &),
                                              vector<pair<ALGraph, Swap>> (*getSubVecinity)(ALGraph &, ALGraph &, int),
                                              int memSize, int vCount,
                                              int aspirationStall, int terminationCond, int maxIterations);

ALGraph tabuSearchWithStructureMemory(ALGraph &g, ALGraph (*heuristic)(ALGraph &),
                                      vector<pair<ALGraph, Swap>> (*getSubVecinity)(ALGraph &, ALGraph &, int),
                                      int memSize, int vCount,
                                      int aspirationStall, int terminationCond, int maxIterations);

#endif //CODE_ALGORITHMS_H
