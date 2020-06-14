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
typedef int Degree;
typedef tuple<Vertex, Vertex, Weight> Edge;

bool sortbythr(const tuple<int, int, int>& a, const tuple<int, int, int>& b);

struct Graph{
    vector<tuple<Vertex, Vertex, Weight>> edges;
    int nodes;
    Graph(vector<Edge> es, int ds)
        : edges(es), nodes(ds) {}
};

Graph readGraph();
Graph shortestEdge(Graph g);

#endif //CODE_GRAPHS_H
