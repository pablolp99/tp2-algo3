#include "graphs.h"

using namespace std;

bool sortByWeight(const Edge &a, const Edge &b) {
    return (a.weight < b.weight);
}

ALGraph::ALGraph() {
    nodeCount = 0;
    neighbours = vector<unordered_map<Vertex, Weight>>(0);
    totalWeight = 0;
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

Edge ALGraph::getEdge(Vertex u, Vertex v) {
    return Edge(u, v, this->getNeighbour(u, v));
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

void ALGraph::swapEdge(ALGraph& g, Edge e, Edge k) {
    _deleteEdge(e);
    _deleteEdge(k);
    this->addEdge(e.start, k.end, g.getNeighbour(e.start, k.end));
    this->addEdge(k.start, e.end, g.getNeighbour(k.start, e.end));
}

void ALGraph::_deleteEdge(Edge e) {
    neighbours[e.start].erase(e.end);
    neighbours[e.end].erase(e.start);
    totalWeight-=e.weight;
}

void ALGraph::_sortAL() {
    sort(incidenceList.begin(), incidenceList.end(), sortByWeight);
}

int ALGraph::getTotalWeight(){
    return totalWeight;
}