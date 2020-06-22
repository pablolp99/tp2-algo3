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

struct Edge {
    Edge(Vertex s, Vertex e, Weight w) : start(s), end(e), weight(w) {}

    Vertex start;
    Vertex end;
    Weight weight;
};

struct Node {
    Node(Vertex _v, Weight _w) : vertex(_v), weight(_w) {}

    Vertex vertex;
    Weight weight;
};

class ALGraph {
public:
    ALGraph(int n);

    int getNodeCount();

    void addEdge(Vertex u, Vertex v, Weight w);

    void addSimpleEdge(Vertex u, Vertex v, Weight w);

    Node getEdge(Vertex u, Vertex v);

    vector<Node> getEdges(Vertex u);

    vector<Edge> getIncidenceList();

    void sortAL();

private:
    int nodeCount;
    vector<vector<Node>> neighbours;
    vector<Edge> incidenceList;

    void _sortAL();
};

bool sortByVertex(const Node &a, const Node &b);

bool sortByWeight(const Edge &a, const Edge &b);

#endif //CODE_GRAPHS_H
