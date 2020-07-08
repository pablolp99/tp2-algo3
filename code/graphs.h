//
// Created by pablo on 6/13/20.
//

#ifndef CODE_GRAPHS_H
#define CODE_GRAPHS_H

#include <vector>
#include <bits/stdc++.h>
#include <unordered_map>

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

class ALGraph {
public:
    ALGraph();

    ALGraph(int n);

    int getNodeCount();

    void addEdge(Vertex u, Vertex v, Weight w);

    Edge getEdge(Vertex u, Vertex v);

    int getNeighbour(Vertex u, Vertex v);

    unordered_map<Vertex, Weight> getNeighbours(Vertex u);

    vector<unordered_map<Vertex, Weight>> getAllNeighbours();

    vector<Edge> getIncidenceList();

    void sortAL();

    void swapEdge(ALGraph& g, Edge, Edge);

    int getTotalWeight();

    bool isCycle();

private:
    int nodeCount;
    vector<unordered_map<Vertex, Weight>> neighbours;
//    Puto el que lee
    vector<Edge> incidenceList;
    int totalWeight;

    void _sortAL();
    void _deleteEdge(Edge);
};

bool sortByWeight(const Edge &a, const Edge &b);

#endif //CODE_GRAPHS_H
