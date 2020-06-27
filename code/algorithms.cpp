#include "algorithms.h"
#include <iostream>
#include "graphs.hpp"
#include "unionfind.hpp"
#include <stack>
#include <cmath>


ALGraph readALGraph() {
    int n, m;
    cin >> n >> m;
    ALGraph g(n);

    for (int i = 0; i < m; ++i) {
        Vertex u, v;
        Weight w;
        cin >> u >> v >> w;
        g.addEdge(u - 1, v - 1, w);
    }

    return g;
}

Node minimumEdge(ALGraph &g, int &v, vector<bool> &flag) {
    Node w = g.getEdge(v, 0);
    w.weight = INFINITY;

    for (int i = 0; i < g.getNeighboursFrom(v).size(); ++i) {
        Node temp = g.getEdge(v, i);
        if (!flag[temp.vertex] && (temp.weight < w.weight)) {
            w = temp;
        }
    }

    return w;
}

vector<int> nearestNeighbour(ALGraph &g) {
    int nodeCount = g.getNodeCount();
    int v = 0;
    int totalWeight = 0;
    vector<int> nodes = {v};
    vector<bool> flag(nodeCount);
    flag[v] = true;

    while (nodes.size() < nodeCount) {
        Node w = minimumEdge(g, v, flag);
        nodes.push_back(w.vertex);
        flag[w.vertex] = true;
        v = w.vertex;
        totalWeight+=w.weight;
    }
//    nodes.push_back(0);
    return nodes;
}

vector<Edge> shortestEdge(ALGraph &g) {
    vector<Edge> sol;
    vector<Degree> deg(g.getNodeCount(), 0);
    UnionFind uf = UnionFind(g.getNodeCount());
    g.sortAL();

    for (Edge e : g.getIncidenceList()) {
        bool fromDiffGroups = uf.find(e.start) != uf.find(e.end);
        bool nodesNotSaturated = deg[e.start] <= 1 && deg[e.end] <= 1;
        if (fromDiffGroups && nodesNotSaturated) {
            sol.push_back(e);
            ++deg[e.start];
            ++deg[e.end];
            uf.unionTree(e.start, e.end);
        }
    }

//    closeCircuit(g, sol, deg);

    return sol;
}

ALGraph kruskalMST(ALGraph g) {
    UnionFind uf(g.getIncidenceList().size());
    g.sortAL();
    ALGraph sol(g.getNodeCount());
    for (Edge e : g.getIncidenceList()) {
        if (uf.find(e.start) != uf.find(e.end)) {
            sol.addEdge(e.start, e.end, e.weight);
            uf.unionTree(e.start, e.end);
        }
    }

    return sol;
}

vector<int> DFS(ALGraph &g) {
    int next = 0;
    int root = 1;
    stack<Vertex> list;
    vector<bool> visited(g.getNodeCount(), false);
    vector<int> order(g.getNodeCount(), 0);

    list.push(root);
    visited[root] = true;
    order[root] = next;

    while (!list.empty()) {
        Vertex u = list.top();
        bool found = false;
        for (Node n : g.getNeighboursFrom(u)) {
            if (!visited[n.vertex]) {
                ++next;
                order[n.vertex] = next;
                list.push(n.vertex);
                visited[n.vertex] = true;
                found = true;
                break;
            }
        }
        if (!found) {
            list.pop();
        }
    }

    return order;
}

vector<int> heuristicAGM(ALGraph &g) {
    ALGraph temp_graph = kruskalMST(g);
    vector<int> order = DFS(temp_graph);
    order.push_back(0);
    int total_weight = 0;
    for (int i = 0; i < order.size() - 1; ++i) {
        for (Node n : g.getNeighboursFrom(order[i])) {
            if (n.vertex == order[i + 1]) {
                total_weight += n.weight;
                break;
            }
        }
    }

    return order;
}

//ALGraph localSearch(ALGraph &g) {
//    ALGraph cycle = shortestEdge(g);
//
//}

//ALGraph tabuSearch(ALGraph &g, int h, int t, int epochs) {
//    switch (h){
//        case 0 :
//            break;
//        case 1 : {
//    ALGraph cycle = shortestEdge(g);
//            break;
//        }
//        default :
//            break;
//    }
//    ALGraph best_cycle = cycle;
//    vector<int> memoria(t);
//    for (int i = 0; i < epochs; ++i){
//        vecinos = localSearch()
//        ciclo = mejorCiclo()
//        memoria.recordarCiclo()
//        if (costo(ciclo) < costo(mejorCiclo)){
//            mejorCiclo = ciclo;
//        }
//    }
//}