#include "algorithms.h"
#include <iostream>
#include "graphs.hpp"
#include "unionfind.hpp"
#include <stack>
#include <cmath>
#include <set>

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

ALGraph heuristicAGM(ALGraph &g) {
    ALGraph temp_graph = kruskalMST(g);
    vector<int> order = DFS(temp_graph);
    ALGraph solution(g.getNodeCount());
    order.push_back(0);
    for (int i = 0; i < order.size() - 1; ++i){
        solution.addEdge(order[i], order[i+1], g.getNeighbour(order[i], order[i + 1]));
    }

    return solution;
}

vector<ALGraph> getHeaviestEdgeSubVicinity(ALGraph& g, ALGraph& cycle){
//    Arista mas pesada
    vector<ALGraph> vicinity;
    vector<ALGraph> bestVicinity(10);
    Edge heaviest(UNDEFINED, UNDEFINED, UNDEFINED);
    for (int i = 0; i < cycle.getNodeCount(); ++i){
        for (auto e : cycle.getNeighbours(i)){
            if (e.second >= heaviest.weight){
                heaviest = Edge(i, e.first, e.second);
            }
        }
    }

    for (int i = 0; i < g.getNodeCount(); ++i){
        for (int j = 0; j < g.getNodeCount(); ++j){
            if (i != heaviest.start && i != heaviest.end &&
                j != heaviest.start && j != heaviest.end &&
                i < j){
                ALGraph temp = cycle;
                temp.swapEdge(g, heaviest, g.getEdge(i, j));
                vicinity.push_back(temp);
            }
        }
    }

    for (int cancer = 0; cancer < 10; ++cancer){
        bestVicinity[cancer] = vicinity[cancer];
    }

    for (int l = 0; l < vicinity.size(); ++l){
        bool is_min = false;
        int temp_best = UNDEFINED;
        for (int p = 0; p < bestVicinity.size(); ++p){
            if (vicinity[l].getTotalWeight() < bestVicinity[p].getTotalWeight()){
                is_min = true;
                temp_best = l;
            }
        }
        if (is_min){
            int temp_worse = 0;
            int temp_idx = 0;
            for (int k = 0; k < bestVicinity.size(); ++k){
                if (bestVicinity[k].getTotalWeight() > temp_worse){
                    temp_idx = k;
                    temp_worse = bestVicinity[k].getTotalWeight();
                }
            }
            bestVicinity[temp_idx] = vicinity[temp_best];
        }
    }

   return vicinity;
}

void findBestCycle(vector<ALGraph>& vicinity, vector<int>& memory){
    ALGraph bestCycle = vicinity[0];
    for (int i = 1; i < vicinity.size(); ++i){
        if (vicinity[i].getTotalWeight() < bestCycle.getTotalWeight()){
            bestCycle = vicinity[i];
        }
    }
}

void tabuSearchExplored(ALGraph &g, ALGraph (*heuristic)(ALGraph&), int memSize, int terminationCond){
    ALGraph cycle = heuristic(g);
    ALGraph bestYet = cycle;
//    Memory Based: Caracteristicas de las soluciones
    vector<int> memory(memSize, UNDEFINED);
    memory[0] = bestYet.getTotalWeight();
    int iterations = 0;
//    while (iterations < terminationCond){
    vector<ALGraph> subVicinity = getHeaviestEdgeSubVicinity(g, cycle);
//        cycle =

//    }
}
