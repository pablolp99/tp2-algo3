#include <vector>
#include "unionfind.h"

UnionFind::UnionFind(int n) {
    height = vector<int>(n,1);
    father = vector<int>(n);
    for (int i = 0; i < n; ++i){
        father[i] = i;
    }
}

int UnionFind::find(int n){
    if (father[n] != n){
        father[n] = find(father[n]);
    }
    return father[n];
}

void UnionFind::unionTree(int a, int b){
    a = find(a);
    b = find(b);
    if (height[a] < height[b]){
        father[a] = b;
    } else {
        father[b] = a;
    }
    if (height[a] == height[b]){
        ++height[a];
    }
}
