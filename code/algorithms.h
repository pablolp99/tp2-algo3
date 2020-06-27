//
// Created by pablo on 6/19/20.
//

#ifndef CODE_ALGORITHMS_H
#define CODE_ALGORITHMS_H

#include "graphs.h"
#include <vector>

ALGraph readALGraph();

Node minimumEdge();

//vector<int> nearestNeighbour(ALGraph &g);
vector<int> nearestNeighbour(ALGraph &g);

//ALGraph shortestEdge(ALGraph &g);
vector<Edge> shortestEdge(ALGraph &g);

ALGraph kruskalMST(ALGraph g);

vector<int> DFS(ALGraph &g);

//pair<vector<int>, int> heuristicAGM(ALGraph &g);
vector<int> heuristicAGM(ALGraph &g);

ALGraph localSearch(ALGraph &g);

ALGraph tabuSearch(int h);

#endif //CODE_ALGORITHMS_H
