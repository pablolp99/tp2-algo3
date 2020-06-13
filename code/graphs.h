//
// Created by pablo on 6/13/20.
//

#ifndef CODE_GRAPHS_H
#define CODE_GRAPHS_H

#include <vector>

// Adjacency List Graph (ALGraph)
typedef int Vertex;
typedef int Weight;
struct Neighbour{
    Vertex dst;
    Weight wgh;
    Neighbour(Vertex d, Weight w)
            : dst(d), wgh(w) {}
};
typedef std::vector<std::vector<Neighbour>> ALGraph;

ALGraph readAlgraph(int& v0);
ALGraph shortestEdge(ALGraph g);


#endif //CODE_GRAPHS_H
