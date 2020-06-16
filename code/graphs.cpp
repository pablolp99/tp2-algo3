#include <iostream>
#include "graphs.h"
#include "unionfind.hpp"
#include <bits/stdc++.h>

using namespace std;

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
        g[u-1].push_back(make_pair(v-1,w));
        g[v-1].push_back(make_pair(u-1,w));
    }
    return g;
}

pair<Vertex, Weight> minimumEdge(ALGraph& g, int& v, vector<bool>& flag){
    pair<Vertex, Weight> w = g[v][0];
    get<1>(w) = INFINITY;
    for (int i = 0; i < g[v].size(); ++i){
        pair<Vertex, Weight> temp = g[v][i];
        if (!flag[get<0>(temp)] && (get<1>(temp) < get<1>(w))){
            w = temp;
        }
    }
    return w;
}

vector<int> nearestNeighbour(ALGraph g){
    int v = 0;
    vector<int> nodes = {v};
    int nodeCount = g.size();
    vector<bool> flag(nodeCount);
    flag[v] = true;
    while (nodes.size() < nodeCount){
        pair<Vertex, Weight> w = minimumEdge(g, v, flag);
        nodes.push_back(get<0>(w));
        flag[get<0>(w)] = true;
        v = get<0>(w);
    }
    nodes.push_back(0);
    return nodes;
}

Graph shortestEdge(Graph g){
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
    return Graph(sol, g.nodeCount);
}
