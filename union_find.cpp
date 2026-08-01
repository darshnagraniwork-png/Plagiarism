#include <iostream>
#include <vector>
using namespace std;

class UnionFind {
    vector<int> parent;
public:
    UnionFind(int size) {
      
        parent.resize(size);
      
        for (int i = 0; i < size; i++) {
            parent[i] = i;
        }
    }

    int find(int i) {
      
        if (parent[i] == i) {
            return i;
        }
        return find(parent[i]);
    }

    void unite(int i, int j) {
      
        int irep = find(i);
      
        int jrep = find(j);
       
        parent[irep] = jrep;
    }
};
