#include "graphs.h"

using namespace std;

ALGraph::ALGraph(int n){
    nodeCount = n;
    vector<vector<Node>> _v(n);
    neighbours = _v;
}

int ALGraph::getNodeCount() {
    return nodeCount;
}

void ALGraph::addEdge(Vertex u, Vertex v, Weight w) {
    neighbours[u].push_back(Node(v, w));
    neighbours[v].push_back(Node(u, w));
    incidenceList.push_back(Edge(u, v, w));
}

Node ALGraph::getEdge(Vertex u, Vertex v) {
    return neighbours[u][v];
}

vector<Node> ALGraph::getEdges(Vertex u) {
    return neighbours[u];
}

vector<Edge> ALGraph::getIncidenceList() {
    return incidenceList;
}
