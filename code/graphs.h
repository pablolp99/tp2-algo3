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
typedef int Degree;

bool sortbythr(const tuple<int, int, int>& a, const tuple<int, int, int>& b);

struct Graph{
    vector<Edge> edges;
    int nodeCount;
    Graph(vector<Edge> es, int ds)
        : edges(es), nodeCount(ds) {}
};

struct Node{
    Node(Vertex _v, Weight _w) : vertex(_v), weight(_w) {}
    Vertex vertex;
    Weight weight;
};

class ALGraph{
public:
    ALGraph(int n);

    void addEdge(Vertex u, Vertex v, Weight w);
    Node getEdge(Vertex u, Vertex v);
    vector<Node> getEdges(Vertex u);
    int getNodeCount();

private:
    int nodeCount;
    vector<vector<Node>> neighbours;
};

#endif //CODE_GRAPHS_H
