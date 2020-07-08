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

// O(M log(M))
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

//
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

vector<ALGraph> getHeaviestEdgeSubVicinity(ALGraph& g, ALGraph& cycle, int vCount){
//    Arista mas pesada
    vector<ALGraph> vicinity;
    vector<ALGraph> bestVicinity;
    Edge heaviest(UNDEFINED, UNDEFINED, UNDEFINED);
    for (int i = 0; i < cycle.getNodeCount(); ++i){
        for (auto e : cycle.getNeighbours(i)){
            if (e.second >= heaviest.weight){
                heaviest = Edge(i, e.first, e.second);
            }
        }
    }

    ALGraph temp;
    for (int i = 0; i < g.getNodeCount(); ++i){
        for (int j = 0; j < g.getNodeCount(); ++j){
            if (i != heaviest.start && i != heaviest.end &&
                j != heaviest.start && j != heaviest.end &&
                i < j){
                if (cycle.getNeighbours(i).find(j) != cycle.getNeighbours(i).end()){
                    temp = cycle;
                    temp.swapEdge(g, heaviest, g.getEdge(i, j));
                    vicinity.push_back(temp);
                }
            }
        }
    }

    for (int idx = 0; idx < vCount && idx < g.getNodeCount() && idx < vicinity.size(); ++idx){
        bestVicinity.push_back(vicinity[idx]);
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

vector<ALGraph> getRandomSubVicinity(ALGraph& g, ALGraph& cycle, int vCount) {
    vector<ALGraph> vicinity;
    vector<ALGraph> bestVicinity;
    Edge randomEdge(UNDEFINED, UNDEFINED, UNDEFINED);
    Vertex random = rand() % g.getNodeCount();
    cout << "Vertex random: " << random << endl;
    int randomEdgePos = rand() % cycle.getNeighbours(random).size();

    int k = 0;
    for (auto neighbour : cycle.getNeighbours(random)) {
        if (randomEdgePos == k) { randomEdge = Edge(random, neighbour.first, neighbour.second); }
        ++k;
    }

    ALGraph temp;
    for (int i = 0; i < g.getNodeCount(); ++i){
        for (int j = 0; j < g.getNodeCount(); ++j){
            if (i != randomEdge.start && i != randomEdge.end &&
                j != randomEdge.start && j != randomEdge.end &&
                i < j){
                if (cycle.getNeighbours(i).find(j) != cycle.getNeighbours(i).end()){
                    temp = cycle;
                    temp.swapEdge(g, randomEdge, g.getEdge(i, j));
                    vicinity.push_back(temp);
                }
            }
        }
    }

    for (int idx = 0; idx < vCount && idx < g.getNodeCount() && idx < vicinity.size(); ++idx){
        bestVicinity.push_back(vicinity[idx]);
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

int findBestCycle(vector<ALGraph>& vicinity, vector<int>& memory, int vCount, bool flag, int& stopCond){
    int pos;
    if (vicinity.size() < vCount){
        pos = rand() % vicinity.size();
    } else {
        pos = rand() % vCount;
    }
    ALGraph randomCycle = vicinity[pos];
    if (!flag){
        for (int i = 0; i < memory.size(); ++i){
            if (randomCycle.getTotalWeight() == memory[i]){
                return -1;
            }
        }
    } else {
        ++stopCond;
    }
    return pos;
}

ALGraph tabuSearchExplored(ALGraph &g, ALGraph (*heuristic)(ALGraph&), int memSize, int vCount, int aspirationStall, int terminationCond, int maxIterations){
    ALGraph cycle = heuristic(g);
    ALGraph original = cycle;
//    Memory Based: Caracteristicas de las soluciones
    vector<int> memory(memSize, UNDEFINED);
    memory[0] = cycle.getTotalWeight();
    int idx = 1;
    int stall = 0;
    int stopCond = 0;
    int iter = 0;
    vector<ALGraph> subVicinity;

    while (stopCond <= terminationCond && iter < maxIterations) {
//        subVicinity = getHeaviestEdgeSubVicinity(g, cycle, vCount);
        subVicinity = getRandomSubVicinity(g, cycle, vCount);
        int pos = findBestCycle(subVicinity, memory, vCount, aspirationStall <= stall, stopCond);
        if (pos != -1) {
            if (idx < memSize) {
                memory[idx] = subVicinity[pos].getTotalWeight();
                ++idx;
            } else {
                idx = 0;
                int randMemPos = rand() % memory.size();
                memory[randMemPos] = subVicinity[pos].getTotalWeight();
            }

            if (subVicinity[pos].getTotalWeight() < cycle.getTotalWeight()) {
                cycle = subVicinity[pos];
                stall = 0;
                stopCond = 0;
            }
        } else {
            ++stall;
        }
        ++iter;
    }

    return cycle;
}