#include <bits/stdc++.h>
using namespace std;

int kruskalsMST(int V, vector<vector<int>>& edges) {
    vector<int> parent(V);
    vector<int> rank(V, 1);
    
    for (int i = 0; i < V; i++) {
        parent[i] = i;
    }

    function<int(int)> find = [&](int i) {
        return (parent[i] == i) ? i : (parent[i] = find(parent[i]));
    };

    auto unite = [&](int x, int y) {
        int s1 = find(x), s2 = find(y);
        if (s1 != s2) {
            if (rank[s1] < rank[s2]) parent[s1] = s2;
            else if (rank[s1] > rank[s2]) parent[s2] = s1;
            else {
                parent[s2] = s1;
                rank[s1]++;
            }
        }
    };

    sort(edges.begin(), edges.end(), [](vector<int>& a, vector<int>& b) {
        return a[2] < b[2];
    });

    int cost = 0, count = 0;
    
    for (auto& e : edges) {
        int x = e[0], y = e[1], w = e[2];
        
        if (find(x) != find(y)) {
            unite(x, y);
            cost += w;
            if (++count == V - 1) break;
        }
    }
    
    return cost;
}
