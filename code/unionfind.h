#ifndef CODE_TREE_H
#define CODE_TREE_H

#include <vector>

using namespace std;

// UnionFind
class UnionFind{
public:
    UnionFind(int n);
    int find(int n);
    void unionTree(int a, int b);
private:
    vector<int> height;
    vector<int> father;
};

#endif //CODE_TREE_H