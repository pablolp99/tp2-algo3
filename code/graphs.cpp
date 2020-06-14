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

Graph shortestEdge(Graph g){
    vector<Edge> sol;
    vector<Degree> deg(g.nodes, 0);
    UnionFind uf = UnionFind(g.nodes);
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
    return Graph(sol, g.nodes);
}