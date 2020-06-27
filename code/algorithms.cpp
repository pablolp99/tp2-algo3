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

int minimumEdge(ALGraph &g, int &v, vector<bool> &flag) {
    int w = INFINITY;
    int res = 0;
    for (int i = 0; i < g.getNeighbours(v).size(); ++i) {
        int temp = g.getNeighbour(v, i);
        if (!flag[i] && (temp < w)) {
            v = i;
            w = temp;
        }
    }

    return res;
}

vector<int> nearestNeighbour(ALGraph &g) {
    int nodeCount = g.getNodeCount();
    int v = 0;
    vector<int> nodes = {v};
    vector<bool> flag(nodeCount);
    flag[v] = true;

    while (nodes.size() < nodeCount) {
        int w = minimumEdge(g, v, flag);
        nodes.push_back(w);
        flag[w] = true;
        v = w;
    }
    nodes.push_back(0);
    return nodes;
}

void closeCircuit(ALGraph g, vector<Edge> &sol, vector<Degree> deg) {
    int a, b = 0;

    for (int i = 0; i < deg.size(); ++i) {
        if (deg[i] != 1) {
            continue;
        }
        //Then deg[i] == 1
        a = i;
    }

    for (Edge e : g.getIncidenceList()) {
        if ((e.start == b && e.end == a) || (e.end == b && e.start == a)) {
            sol.push_back(e);
            break;
        }
    }
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

    closeCircuit(g, sol, deg);

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
    int root = 0;
    stack<int> list;
    vector<bool> visited(g.getNodeCount(), false);
    vector<int> order(g.getNodeCount(), 0);

    list.push(root);
    visited[root] = true;
    order[root] = next;

    while (!list.empty()) {
        int u = list.top();
        bool found = false;
        for (auto n : g.getNeighbours(u)) {
            if (!visited[n.first]) {
                ++next;
                order[n.first] = next;
                list.push(n.first);
                visited[n.first] = true;
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

pair<vector<int>, int> heuristicAGM(ALGraph &g) {
    ALGraph temp_graph = kruskalMST(g);
    vector<int> order = DFS(temp_graph);
    order.push_back(0);
    int total_weight = 0;
    for (int i = 0; i < order.size() - 1; ++i) {
        for (auto n : g.getNeighbours(order[i])) {
            if (n.first == order[i + 1]) {
                total_weight += n.second;
                break;
            }
        }
    }
    order.pop_back();

    return make_pair(order, total_weight);
}
