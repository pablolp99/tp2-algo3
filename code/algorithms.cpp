#include "algorithms.h"
#include <iostream>
#include "graphs.hpp"
#include "unionfind.hpp"
#include <bits/stdc++.h>

bool sortbythr(const tuple<int, int, int>& a, const tuple<int, int, int>& b){
    return (get<2>(a) < get<2>(b));
}

Graph readGraph(){
    int n, m;
    cin >> n >> m;
    vector<tuple<Vertex, Vertex, Weight>> edges;
    for (int i = 0; i < m; ++i){
        Vertex a,b;
        Weight w;
        cin >> a >> b >> w;
        edges.push_back(make_tuple(a-1,b-1,w));
    };
    return Graph(edges, n);
}

ALGraph readALGraph(){
    int n, m;
    cin >> n >> m;
    ALGraph g(n);
    for (int i = 0; i < m; ++i){
        Vertex u,v;
        Weight w;
        cin >> u >> v >> w;
        g.addEdge(u-1, v-1, w);
    }
    return g;
}

Node minimumEdge(ALGraph& g, int& v, vector<bool>& flag){
    Node w = g.getEdge(v, 0);
    w.weight = INFINITY;
    for (int i = 0; i < g.getEdges(v).size(); ++i){
        Node temp = g.getEdge(v, i);
        if (!flag[temp.vertex] && (temp.weight < w.weight)){
            w = temp;
        }
    }
    return w;
}

vector<int> nearestNeighbour(ALGraph& g){
    int v = 0;
    vector<int> nodes = {v};
    int nodeCount = g.getNodeCount();
    vector<bool> flag(nodeCount);
    flag[v] = true;
    while (nodes.size() < nodeCount){
        Node w = minimumEdge(g, v, flag);
        nodes.push_back(w.vertex);
        flag[w.vertex] = true;
        v = w.vertex;
    }
    nodes.push_back(0);
    return nodes;
}

void closeCircuit(Graph g, vector<Edge>& sol, vector<Degree> deg){
    int a,b = 0;
    bool find_a = false;
    for (int i = 0; i < deg.size(); ++i){
        if (deg[i] == 1){
            if (!find_a){
                a = i;
                find_a = true;
            } else {
                a = i;
            }
        }
    }
    for (Edge e : g.edges){
        if ((get<0>(e) == b && get<1>(e) == a) || (get<1>(e) == b && get<0>(e) == a)){
            sol.push_back(e);
            break;
        }
    }
}

vector<Edge> shortestEdge(Graph& g){
    vector<Edge> sol;
    vector<Degree> deg(g.nodeCount, 0);
    UnionFind uf = UnionFind(g.nodeCount);
    sort(g.edges.begin(), g.edges.end(), sortbythr);
    for (Edge e : g.edges){
        if (uf.find(get<0>(e)) != uf.find(get<1>(e))){
            if (deg[get<0>(e)] <= 1 && deg[get<1>(e)] <= 1){
                sol.push_back(e);
                ++deg[get<0>(e)];
                ++deg[get<1>(e)];
                uf.unionTree(get<0>(e), get<1>(e));
            }
        }
    }
    closeCircuit(g, sol, deg);
    return sol;
}

ALGraph kruskalMST(Graph g){
    UnionFind uf(g.edges.size());
    sort(g.edges.begin(), g.edges.end(), sortbythr);
    ALGraph sol(g.nodeCount);
    for (Edge e : g.edges){
        if (uf.find(get<0>(e)) != uf.find(get<1>(e))){
            sol.addEdge(get<0>(e), get<1>(e), get<2>(e));
            uf.unionTree(get<0>(e), get<1>(e));
        }
    }
    return sol;
}

vector<int> dfs(ALGraph& g){
    int next = 0;
    int root = 0;
    stack<int> list;
    vector<bool> visited(g.getNodeCount(), false);
    vector<int> pred(g.getNodeCount(), 0);
    vector<int> order(g.getNodeCount(), 0);

    list.push(root);
    visited[root] = true;
    order[root] = next;

    while (!list.empty()){
        int u = list.top();
        int w = -1;
        for (int i = 0; i < g.getEdges(u).size(); ++i){
            if (!visited[g.getEdge(u,i).vertex]){
                w = g.getEdge(u,i).vertex;
                pred[w] = u;
                ++next;
                order[w] = next;
                list.push(w);
                visited[w]=true;
                break;
            }
        }
        if (w == -1){
            list.pop();
        }
    }
    return order;
}

void heurisitcAgm(Graph& g){
    ALGraph gp = kruskalMST(g);
    int k;
}
