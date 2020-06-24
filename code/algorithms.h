//
// Created by pablo on 6/19/20.
//

#ifndef CODE_ALGORITHMS_H
#define CODE_ALGORITHMS_H

#include "graphs.h"
#include <vector>

ALGraph readALGraph();

void closeCircuit(ALGraph g, vector<Edge> &sol, vector<Degree> deg);

vector<Edge> shortestEdge(ALGraph &g);

Node minimumEdge();

vector<int> nearestNeighbour(ALGraph &g);

ALGraph kruskalMST(ALGraph g);

vector<int> DFS(ALGraph &g);

pair<vector<int>, int> heuristicAGM(ALGraph &g);


#endif //CODE_ALGORITHMS_H
