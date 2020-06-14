#include <iostream>
#include "graphs.h"
#include "unionfind.hpp"
using namespace std;

Graph readGraph(){
    int n, m;
    cin >> n >> m;
    vector<Edge> edges;
    // El degree 0 no vale nada. Solo esta por la generacion
    // del vector de degrees
    vector<Degree> degrees(n, 0);
    for (int i = 0; i < m; ++i){
        Vertex a,b;
        Weight k;
        cin >> a >> b >> k;
        ++degrees[a];
        ++degrees[b];
        edges.push_back(Edge(a,b,k));
    }
    return Graph(edges, degrees);
}