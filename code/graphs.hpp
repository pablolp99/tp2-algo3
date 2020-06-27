#include "graphs.h"

using namespace std;

bool sortByVertex(const Node &a, const Node &b) {
    return (a.vertex < b.vertex);
}

bool sortByWeight(const Edge &a, const Edge &b) {
    return (a.weight < b.weight);
}

ALGraph::ALGraph(int n) {
    nodeCount = n;
    neighbours = vector<vector<Node>>(n);
    totalWeight = 0;
}

int ALGraph::getNodeCount() {
    return nodeCount;
}

void ALGraph::addEdge(Vertex u, Vertex v, Weight w) {
    neighbours[u].push_back(Node(v, w));
    neighbours[v].push_back(Node(u, w));
    incidenceList.push_back(Edge(u, v, w));
    totalWeight += w;
}

Node ALGraph::getEdge(Vertex u, Vertex v) {
    return neighbours[u][v];
}

vector<Node> ALGraph::getNeighboursFrom(Vertex u) {
    return neighbours[u];
}

vector<Edge> ALGraph::getIncidenceList() {
    return incidenceList;
}

void ALGraph::sortAL() {
    _sortAL();
}

void ALGraph::_sortAL() {
    sort(incidenceList.begin(), incidenceList.end(), sortByWeight);
}