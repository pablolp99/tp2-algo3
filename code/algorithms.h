//
// Created by pablo on 6/19/20.
//

#ifndef CODE_ALGORITHMS_H
#define CODE_ALGORITHMS_H

#include "graphs.h"
#include <vector>

Graph readGraph();
ALGraph readALGraph();

void closeCircuit(Graph g, vector<Edge>& sol, vector<Degree> deg);
vector<Edge> shortestEdge(Graph& g);

Node minimumEdge();
vector<int> nearestNeighbour(ALGraph& g);

ALGraph kruskalMST(Graph g);
vector<int> dfs(ALGraph& g);
//void heurisitcAgm(Graph& g);


#endif //CODE_ALGORITHMS_H
