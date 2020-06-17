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

vector<int> nearestNeighbour(ALGraph& g){
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
    return sol;
}

ALGraph primMST(ALGraph& g){
    vector<int> distance(g.size(), INFINITY);
    vector<bool> visited(g.size(), false);
    priority_queue<pair<int, int>, vector<pair<int,int>>, greater<pair<int, int>> > queue;

    int s = 0;
    distance[s] = 0;
    queue.push(make_pair(s, distance[s]));

    ALGraph res(g.size());

    while (!queue.empty()){
        pair<int, int> u = queue.top();
        queue.pop();
        if (visited[u.first]){
            continue;
        }
        visited[u.first] = true;
        for (pair<int, int> w : g[u.first]){
            if (!visited[w.first] && distance[w.first] > w.second){
                distance[w.first] = w.second;
                res[u.first].push_back(w);
                res[w.first].push_back(make_pair(u.first, w.second));
                queue.push(w);
            }
        }
    }
    return res;
}

pair<vector<int>, vector<int>> dfs(ALGraph& g){
    int next = 1;
    int root = 0;
    stack<int> list;
    vector<bool> visited(g.size(), false);
    vector<int> pred(g.size(), 0);
    vector<int> order(g.size(), 0);

    list.push(root);
    visited[root] = true;
    order[root] = next;

    while (!list.empty()){
        int u = list.top();
        int w = -1;
        for (int i = 0; i < g[u].size(); ++i){
            if (!visited[g[u][i].first]){
                w = g[u][i].first;
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
    return make_pair(pred, order);
}

void heurisitcAgm(ALGraph g){

}