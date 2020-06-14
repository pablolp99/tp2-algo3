//
// Created by pablo on 6/13/20.
//

#ifndef CODE_GRAPHS_H
#define CODE_GRAPHS_H

#include <vector>

using namespace std;

typedef int Vertex;
typedef int Weight;
typedef int Degree;

struct Edge{
    Vertex u;
    Vertex v;
    Weight weight;
    Edge(Vertex v1, Vertex v2, Weight w)
        : u(v1), v(v2), weight(w) {}
};

struct Graph{
    vector<Edge> edges;
    vector<Degree> degrees;
    Graph(vector<Edge> es, vector<Degree> ds)
        : edges(es), degrees(ds) {}
};

Graph readGraph();

#endif //CODE_GRAPHS_H
