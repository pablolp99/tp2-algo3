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

vector<int> minimumEdge(ALGraph &g, int &v, vector<bool> &flag){
    int w = INFINITY;
    vector<int> pair(2);
    for (auto e : g.getNeighbours(v)){
        if (!flag[e.first] && (e.second < w)){
            w = e.second;
            pair = { e.first, e.second };
        }
    }
    return pair;
}

ALGraph nearestNeighbour(ALGraph &g){
    int v = 0;
    int idx = 0;
    vector<int> w;
    ALGraph solution(g.getNodeCount());
    vector<bool> flag(g.getNodeCount(), false);
    flag[v] = true;

    while (idx < g.getNodeCount()-1){
        w = minimumEdge(g, v, flag);
        flag[w[0]] = true;
        solution.addEdge(v, w[0], w[1]);
        v = w[0];
        ++idx;
    }

    solution.addEdge(0, v, g.getNeighbour(0, v));

    return solution;
}

ALGraph shortestEdge(ALGraph &g) {
    ALGraph sol(g.getNodeCount());
    vector<Degree> deg(g.getNodeCount(), 0);
    UnionFind uf = UnionFind(g.getNodeCount());
    g.sortAL();

    for (Edge e : g.getIncidenceList()) {
        bool fromDiffGroups = uf.find(e.start) != uf.find(e.end);
        bool nodesNotSaturated = deg[e.start] <= 1 && deg[e.end] <= 1;
        if (fromDiffGroups && nodesNotSaturated) {
            sol.addEdge(e.start, e.end, e.weight);
            ++deg[e.start];
            ++deg[e.end];
            uf.unionTree(e.start, e.end);
        }
    }

    int f = -1;
    int s = -1;
    for (int i = 0; i < deg.size(); ++i){
        if (deg[i] == 1){
            if (f == -1){
                f = i;
            } else {
                s = i;
            }
        }
    }

    sol.addEdge(f, s, g.getNeighbour(f, s));

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

void tabuSearch(ALGraph &g, int memSize){

}
