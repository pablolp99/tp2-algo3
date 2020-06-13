//
// Created by pablo on 6/13/20.
//

#ifndef CODE_GRAPHS_H
#define CODE_GRAPHS_H

#include <vector>

// Listas de Adyacencia
typedef int Vertex;
typedef int Weight;
struct Neigbour{
    Vertex dst;
    Weight wgh;
    Neigbour(Vertex d, Weight w)
            : dst(d), wgh(w) {}
};
typedef std::vector<std::vector<Neigbour>> ALGraph;

ALGraph read_graph(int& v0);

#endif //CODE_GRAPHS_H
