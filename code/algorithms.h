#ifndef CODE_ALGORITHMS_H
#define CODE_ALGORITHMS_H

#include "graphs.h"
#include <vector>

#define UNDEFINED (-1)

ALGraph readALGraph();

void closeCircuit(ALGraph g, vector<Edge> &sol, vector<Degree> deg);

//vector<Edge> shortestEdge(ALGraph &g);
ALGraph shortestEdge(ALGraph &g);

//int minimumEdge();
vector<int> minimumEdge(ALGraph &g, int &v, vector<bool> &flag);

//vector<int> nearestNeighbour(ALGraph &g);
ALGraph nearestNeighbour(ALGraph &g);

ALGraph kruskalMST(ALGraph g);

vector<int> DFS(ALGraph &g);

//pair<vector<int>, int> heuristicAGM(ALGraph &g);
ALGraph heuristicAGM(ALGraph &g);

vector<ALGraph> getHeaviestEdgeSubVicinity(ALGraph& g, ALGraph& cycle);

int findBestCycle(vector<ALGraph>& vicinity, vector<int>& memory, bool flag, int& stopCond);

void tabuSearchExplored(ALGraph &g, ALGraph (*heuristic)(ALGraph&), int memSize, int aspirationStall, int terminationCond, int maxIteration);

#endif //CODE_ALGORITHMS_H
