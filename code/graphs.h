//
// Created by pablo on 6/13/20.
//

#ifndef CODE_GRAPHS_H
#define CODE_GRAPHS_H

#include <vector>
#include <bits/stdc++.h>

using namespace std;

typedef int Vertex;
typedef int Weight;
typedef tuple<Vertex, Vertex, Weight> Edge;
typedef set<int> Nodes;
typedef int Degree;

bool sortbythr(const tuple<int, int, int>& a, const tuple<int, int, int>& b);

struct Graph{
    vector<Edge> edges;
    int nodeCount;
    Graph(vector<Edge> es, int ds)
        : edges(es), nodeCount(ds) {}
};

Graph readGraph();
Graph shortestEdge(Graph g);

typedef vector<vector<pair<Vertex, Weight> >> ALGraph;

ALGraph readALGraph();
pair<Vertex, Weight> minimumEdge();
vector<int> nearestNeighbour(ALGraph g);

#endif //CODE_GRAPHS_H
