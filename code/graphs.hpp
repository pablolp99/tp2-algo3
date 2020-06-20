#include "graphs.h"

using namespace std;

ALGraph::ALGraph(int n){
    nodeCount = n;
    vector<vector<Node>> _v(n);
    neighbours = _v;
}

void ALGraph::addEdge(Vertex u, Vertex v, Weight w) {
    neighbours[u].push_back(Node(v, w));
    neighbours[v].push_back(Node(u, w));
}

Node ALGraph::getEdge(Vertex u, Vertex v) {
    return neighbours[u][v];
}

vector<Node> ALGraph::getEdges(Vertex u) {
    return neighbours[u];
}

int ALGraph::getNodeCount() {
    return nodeCount;
}