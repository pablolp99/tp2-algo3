#include "graphs.h"

using namespace std;

bool sortByWeight(const Edge &a, const Edge &b) {
    return (a.weight < b.weight);
}

ALGraph::ALGraph(int n) {
    nodeCount = n;
    neighbours = vector<unordered_map<Vertex, Weight>>(n);
    totalWeight = 0;
}

int ALGraph::getNodeCount() {
    return nodeCount;
}

void ALGraph::addEdge(Vertex u, Vertex v, Weight w) {
    neighbours[u][v] = w;
    neighbours[v][u] = w;
    incidenceList.push_back(Edge(u, v, w));
    totalWeight += w;
}

int ALGraph::getNeighbour(Vertex u, Vertex v) {
    return neighbours[u][v];
}

unordered_map<Vertex, Weight> ALGraph::getNeighbours(Vertex u) {
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
