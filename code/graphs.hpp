#include <algorithm>
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

vector<unordered_map<Vertex, Weight>> ALGraph::getAllNeighbours(){
    return neighbours;
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

    Vertex l = e.start;
    Vertex prev = e.start;

    // Quiero ver que dos nodos estan en la misma componente conexa luego de desconectar las aristas seleccionadas
    // De esta manera se que dos nodos deben ser conectados luego
    // Recorro con l (un nodo de una de las aristas) hasta encontrar alguno de los nodos de la otra arista
    while(l != k.start && l != k.end) {
        // Recorro los vecinos del l actual. Quiero evitar volver al nodo ya recorrido usando prev
        for (auto m : this->getNeighbours(l)) {
            if (m.first != prev) {
                prev = l;
                l = m.first;
                break;
            }
        }
    }

    if (l == k.end){
        this->addEdge(e.start, k.start, g.getNeighbour(e.start, k.start));
        this->addEdge(k.end, e.end, g.getNeighbour(k.end, e.end));
    } else {
        this->addEdge(e.start, k.end, g.getNeighbour(e.start, k.end));
        this->addEdge(k.start, e.end, g.getNeighbour(k.start, e.end));
    }
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

// Funcion debug
bool ALGraph::isCycle() {
    Vertex l = 0;
    Vertex prev = 0;

    for (auto m : this->getNeighbours(l)) {
        l = m.first;
        break;
    }
    int k = 0;
    while(k <= this->getNodeCount()) {
        // Recorro los vecinos del l actual. Quiero evitar volver al nodo ya recorrido usando prev
        for (auto m : this->getNeighbours(l)) {
            if (m.first != prev) {
                prev = l;
                l = m.first;
                break;
            }
        }
        if(l == 0) {
            return true;
        }
        k++;
    }
    return false;
}