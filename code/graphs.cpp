//
// Created by pablo on 6/13/20.
//

#include "graphs.h"
#include <iostream>
using namespace std;

ALGraph read_algraph(int& v0){
    int n, m;
    cin >> n >> m >> v0;
    ALGraph G(n, vector<Neighbour>());
    for (int i = 0; i < m; ++i){
        int v,w,p;
        cin >> v >> w >> p;
        G[v].push_back(Neighbour(w, p));
        G[w].push_back(Neighbour(v, p));
    }
    return G;
}

ALGraph shortestEdge(ALGraph g){
    ALGraph h;

    return h;
}