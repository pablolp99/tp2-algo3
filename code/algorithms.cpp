#include "algorithms.h"
#include <iostream>
#include "graphs.hpp"
#include "unionfind.hpp"
#include <bits/stdc++.h>

bool sortbythr(const Edge& a, const Edge& b){
    return (a.weight < b.weight);
}

//Graph readGraph(){
//    int n, m;
//    cin >> n >> m;
//    vector<tuple<Vertex, Vertex, Weight>> edges;
//    for (int i = 0; i < m; ++i){
//        Vertex a,b;
//        Weight w;
//        cin >> a >> b >> w;
//        edges.push_back(make_tuple(a-1,b-1,w));
//    };
//    return Graph(edges, n);
//}

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

void closeCircuit(ALGraph g, vector<Edge>& sol, vector<Degree> deg){
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
    for (Edge e : g.getIncidenceList()){
        if ((e.start == b && e.end == a) || (e.end == b && e.start == a)){
            sol.push_back(e);
            break;
        }
    }
}

vector<Edge> shortestEdge(ALGraph& g){
    vector<Edge> sol;
    vector<Degree> deg(g.getNodeCount(), 0);
    UnionFind uf = UnionFind(g.getNodeCount());
    vector<Edge> il = g.getIncidenceList();
    sort(il.begin(), il.end(), sortbythr);
    for (Edge e : g.getIncidenceList()){
        if (uf.find(e.start) != uf.find(e.end)){
            if (deg[e.start] <= 1 && deg[e.end] <= 1){
                sol.push_back(e);
                ++deg[e.start];
                ++deg[e.end];
                uf.unionTree(e.start, e.end);
            }
        }
    }
    closeCircuit(g, sol, deg);
    return sol;
}

ALGraph kruskalMST(ALGraph g){
    UnionFind uf(g.getIncidenceList().size());
    sort(g.getIncidenceList().begin(), g.getIncidenceList().end(), sortbythr);
    ALGraph sol(g.getNodeCount());
    for (Edge e : g.getIncidenceList()){
        if (uf.find(e.start) != uf.find(e.end)){
            sol.addEdge(e.start, e.end, e.weight);
            uf.unionTree(e.start, e.end);
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


void heurisitcAgm(ALGraph& g){
    ALGraph gp = kruskalMST(g);
    int k;
}
