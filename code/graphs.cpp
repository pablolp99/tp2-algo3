//
// Created by pablo on 6/13/20.
//

#include "graphs.h"
#include <iostream>
using namespace std;

ALGraph read_graph(int& v0){
    int n, m;
    cin >> n >> m >> v0;
    ALGraph G(n, vector<Neigbour>());
    for (int i = 0; i < m; ++i){
        int v,w,p;
        cin >> v >> w >> p;
        G[v].push_back(Neigbour(w, p));
        G[w].push_back(Neigbour(v, p));
    }
    return G;
}