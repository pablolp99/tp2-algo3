#include "algorithms.h"
#include <iostream>
#include "graphs.hpp"
#include "unionfind.hpp"
#include <stack>
#include <cmath>
#include <ctime>

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

vector<int> minimumEdge(ALGraph &g, int &v, vector<bool> &flag) {
    int w = INFINITY;
    vector<int> pair(2);
    for (auto e : g.getNeighbours(v)) {
        if (!flag[e.first] && (e.second < w)) {
            w = e.second;
            pair = {e.first, e.second};
        }
    }
    return pair;
}

ALGraph nearestNeighbour(ALGraph &g) {
    int v = 0;
    int idx = 0;
    vector<int> w;
    ALGraph solution(g.getNodeCount());
    vector<bool> flag(g.getNodeCount(), false);
    flag[v] = true;

    while (idx < g.getNodeCount() - 1) {
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
    for (int i = 0; i < deg.size(); ++i) {
        if (deg[i] == 1) {
            if (f == -1) {
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

vector<Vertex> neighboursToVisit(ALGraph &g, vector<bool> &visited, Vertex v) {
    vector<Vertex> toVisit;
    for (auto n : g.getNeighbours(v)) {
        if (!visited[n.first]) {
            toVisit.push_back(n.first);
        }
    }
    return toVisit;
}

vector<Vertex> DFS(ALGraph &g) {
    vector<int> order;
    vector<bool> visited(g.getNodeCount(), false);
    stack<Vertex> depth;
    Vertex visiting = 0;

    depth.push(visiting);
    order.push_back(visiting);
    visited[visiting] = true;

    while (!depth.empty()) {
        visiting = depth.top();
        if (!visited[visiting]) {
            depth.push(visiting);
            order.push_back(visiting);
            visited[visiting] = true;
        }

        vector<Vertex> toVisit = neighboursToVisit(g, visited, visiting);
        if (toVisit.empty()) { depth.pop(); continue; }
        depth.push(toVisit[0]);
    }

    return order;
}

ALGraph heuristicAGM(ALGraph &g) {
    ALGraph temp_graph = kruskalMST(g);
    ALGraph solution(g.getNodeCount());
    vector<Vertex> order = DFS(temp_graph);

    order.push_back(0);
    for (int i = 0; i < order.size() - 1; ++i) {
        solution.addEdge(order[i], order[i + 1], g.getNeighbour(order[i], order[i + 1]));
    }

    return solution;
}

vector<pair<ALGraph, Swap>> getHeaviestEdgeSubVicinity(ALGraph &g, ALGraph &cycle, int vCount) {
//    Arista mas pesada
    vector<pair<ALGraph, Swap>> vicinity;
    vector<pair<ALGraph, Swap>> bestVicinity;
    Edge heaviest(UNDEFINED, UNDEFINED, UNDEFINED);
    for (int i = 0; i < cycle.getNodeCount(); ++i) {
        for (auto e : cycle.getNeighbours(i)) {
            if (e.second >= heaviest.weight) {
                heaviest = Edge(i, e.first, e.second);
            }
        }
    }

    ALGraph temp;
    for (int i = 0; i < g.getNodeCount(); ++i) {
        for (int j = 0; j < g.getNodeCount(); ++j) {
            if (i != heaviest.start && i != heaviest.end &&
                j != heaviest.start && j != heaviest.end &&
                i < j) {
                if (cycle.getNeighbours(i).find(j) != cycle.getNeighbours(i).end()) {
                    temp = cycle;
                    temp.swapEdge(g, heaviest, g.getEdge(i, j));
                    vicinity.push_back(make_pair(temp, Swap(heaviest, g.getEdge(i, j))));
                }
            }
        }
    }

    for (int idx = 0; idx < vCount && idx < g.getNodeCount() && idx < vicinity.size(); ++idx) {
        bestVicinity.push_back(vicinity[idx]);
    }

    for (int l = 0; l < vicinity.size(); ++l) {
        bool is_min = false;
        int temp_best = UNDEFINED;
        for (int p = 0; p < bestVicinity.size(); ++p) {
            if (get<0>(vicinity[l]).getTotalWeight() < get<0>(bestVicinity[p]).getTotalWeight()) {
                is_min = true;
                temp_best = l;
            }
        }
        if (is_min) {
            int temp_worse = 0;
            int temp_idx = 0;
            for (int k = 0; k < bestVicinity.size(); ++k) {
                if (get<0>(bestVicinity[k]).getTotalWeight() > temp_worse) {
                    temp_idx = k;
                    temp_worse = get<0>(bestVicinity[k]).getTotalWeight();
                }
            }
            bestVicinity[temp_idx] = vicinity[temp_best];
        }
    }

    return bestVicinity;
}

vector<pair<ALGraph, Swap>> getRandomSubVicinity(ALGraph &g, ALGraph &cycle, int vCount) {
    vector<pair<ALGraph, Swap>> vicinity;
    vector<pair<ALGraph, Swap>> bestVicinity;
    Edge randomEdge(UNDEFINED, UNDEFINED, UNDEFINED);
    Vertex random = rand() % g.getNodeCount();
    int randomEdgePos = rand() % cycle.getNeighbours(random).size();

    int k = 0;
    for (auto neighbour : cycle.getNeighbours(random)) {
        if (randomEdgePos == k) { randomEdge = Edge(random, neighbour.first, neighbour.second); }
        ++k;
    }

    ALGraph temp;
    for (int i = 0; i < g.getNodeCount(); ++i) {
        for (int j = 0; j < g.getNodeCount(); ++j) {
            if (i != randomEdge.start && i != randomEdge.end &&
                j != randomEdge.start && j != randomEdge.end &&
                i < j) {
                if (cycle.getNeighbours(i).find(j) != cycle.getNeighbours(i).end()) {
                    temp = cycle;
                    temp.swapEdge(g, randomEdge, g.getEdge(i, j));
                    vicinity.push_back(make_pair(temp, Swap(randomEdge, g.getEdge(i, j))));
                }
            }
        }
    }

    for (int idx = 0; idx < vCount && idx < g.getNodeCount() && idx < vicinity.size(); ++idx) {
        bestVicinity.push_back(vicinity[idx]);
    }

    for (int l = 0; l < vicinity.size(); ++l) {
        bool is_min = false;
        int temp_best = UNDEFINED;
        for (int p = 0; p < bestVicinity.size(); ++p) {
            if (get<0>(vicinity[l]).getTotalWeight() < get<0>(bestVicinity[p]).getTotalWeight()) {
                is_min = true;
                temp_best = l;
            }
        }
        if (is_min) {
            int temp_worse = 0;
            int temp_idx = 0;
            for (int k = 0; k < bestVicinity.size(); ++k) {
                if (get<0>(bestVicinity[k]).getTotalWeight() > temp_worse) {
                    temp_idx = k;
                    temp_worse = get<0>(bestVicinity[k]).getTotalWeight();
                }
            }
            bestVicinity[temp_idx] = vicinity[temp_best];
        }
    }

    return bestVicinity;
}

int findBestCycle(vector<pair<ALGraph, Swap>> &vicinity, vector<Weight> &memory, int vCount, bool flag, int &stopCond) {
    int pos;
    if (vicinity.size() < vCount) {
        pos = rand() % vicinity.size();
    } else {
        pos = rand() % vCount;
    }
    pair<ALGraph, Swap> randomCycle = vicinity[pos];
    if (!flag) {
        for (int i = 0; i < memory.size(); ++i) {
            if (get<0>(randomCycle).getTotalWeight() == memory[i]) {
                return -1;
            }
        }
    } else {
        ++stopCond;
    }
    return pos;
}

ALGraph tabuSearchWithExploredSolutionsMemory(ALGraph &g, ALGraph (*heuristic)(ALGraph &), int memSize, int vCount,
                                              int aspirationStall, int terminationCond, int maxIterations) {
    ALGraph cycle = heuristic(g);
    ALGraph original = cycle;
//    Memory Based: Caracteristicas de las soluciones
    vector<Weight> memory(memSize, UNDEFINED);
    memory[0] = cycle.getTotalWeight();
    int idx = 1;
    int stall = 0;
    int stopCond = 0;
    int iter = 0;
    vector<pair<ALGraph, Swap>> subVicinity;
    cout << cycle.getTotalWeight() << endl;

    while (stopCond <= terminationCond && iter < maxIterations) {
//        subVicinity = getHeaviestEdgeSubVicinity(g, cycle, vCount);
        subVicinity = getRandomSubVicinity(g, cycle, vCount);
        int pos = findBestCycle(subVicinity, memory, vCount, aspirationStall <= stall, stopCond);
        if (pos != -1) {
            if (idx < memSize) {
//                Guardo en memoria el circuito elegido
                memory[idx] = get<0>(subVicinity[pos]).getTotalWeight();
                ++idx;
            } else {
//                Si la memoria esta llena, elijo una posicion aleatoria para reemplazar
                idx = 0;
                int randMemPos = rand() % memory.size();
                memory[randMemPos] = get<0>(subVicinity[pos]).getTotalWeight();
            }

//            Si encontre una solcion mejor que la que ya tenia hago reset de las condiciones de parada
            if (get<0>(subVicinity[pos]).getTotalWeight() < cycle.getTotalWeight()) {
                cycle = get<0>(subVicinity[pos]);
                stall = 0;
                stopCond = 0;
            }
        } else {
//            Si la solucion hallada esta en la memoria incremento la condicion para ejecutar la funcion de aspiracion
            ++stall;
        }
        ++iter;
    }

    cout << cycle.getTotalWeight() << endl;

    return cycle;
}

int findBestCycleWithSwapMemory(vector<pair<ALGraph, Swap>> &vicinity, vector<Swap> &memory, int vCount, bool flag,
                                int &stopCond) {
    int pos;
    if (vicinity.size() < vCount) {
        pos = rand() % vicinity.size();
    } else {
        pos = rand() % vCount;
    }

    if (!flag) {
        for (int i = 0; i < memory.size(); ++i) {
            if (get<1>(vicinity[pos]) == memory[i]) {
                return -1;
            }
        }
    } else {
        ++stopCond;
    }
    return pos;
}

ALGraph tabuSearchWithStructureMemory(ALGraph &g, ALGraph (*heuristic)(ALGraph &), int memSize, int vCount,
                                      int aspirationStall, int terminationCond, int maxIterations) {
    ALGraph cycle = heuristic(g);
    ALGraph original = cycle;
//    Memory Based: Caracteristicas de las soluciones
    vector<Swap> memory(memSize, Swap(Edge(UNDEFINED, UNDEFINED, UNDEFINED), Edge(UNDEFINED, UNDEFINED, UNDEFINED)));
    //memory[0] = cycle.getTotalWeight();
    int idx = 1;
    int stall = 0;
    int stopCond = 0;
    int iter = 0;
    vector<pair<ALGraph, Swap>> subVicinity;
    cout << cycle.getTotalWeight() << endl;

    while (stopCond <= terminationCond && iter < maxIterations) {
//        subVicinity = getHeaviestEdgeSubVicinity(g, cycle, vCount);
        subVicinity = getRandomSubVicinity(g, cycle, vCount);
        int pos = findBestCycleWithSwapMemory(subVicinity, memory, vCount, aspirationStall <= stall, stopCond);
        if (pos != -1) {
            if (idx < memSize) {
//                Guardo en memoria el circuito elegido
                memory[idx] = get<1>(subVicinity[pos]);
                ++idx;
            } else {
//                Si la memoria esta llena, elijo una posicion aleatoria para reemplazar
                idx = 0;
                int randMemPos = rand() % memory.size();
                memory[randMemPos] = get<1>(subVicinity[pos]);
            }

//            Si encontre una solcion mejor que la que ya tenia hago reset de las condiciones de parada
            if (get<0>(subVicinity[pos]).getTotalWeight() < cycle.getTotalWeight()) {
                cycle = get<0>(subVicinity[pos]);
                stall = 0;
                stopCond = 0;
            }
        } else {
//            Si la solucion hallada esta en la memoria incremento la condicion para ejecutar la funcion de aspiracion
            ++stall;
        }
        ++iter;
    }

    cout << cycle.getTotalWeight() << endl;

    return cycle;
}