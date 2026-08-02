#include <iostream>
#include <vector>
#include <set>
#include <functional>

using namespace std;

vector<int> centroidDecomposition(vector<set<int>>& tree) {
    int n = tree.size();
    vector<int> dad(n);
    vector<int> sub(n);

    function<int(int, int)> dfs_sz = [&](int u, int p) {
        sub[u] = 1;
        for (auto v : tree[u]) {
            if (v != p) {
                sub[u] += dfs_sz(v, u);
            }
        }
        return sub[u];
    };

    function<int(int, int, int)> dfs_centroid = [&](int u, int p, int sz) {
        for (auto v : tree[u]) {
            if (v != p && sub[v] > sz / 2) {
                return dfs_centroid(v, u, sz);
            }
        }
        return u;
    };

    function<void(int, int)> build = [&](int u, int p) {
        int sz = dfs_sz(u, p);
        int centroid = dfs_centroid(u, p, sz);
        
        if (p == -1) p = centroid;
        dad[centroid] = p;
        
        vector<int> neighbors(tree[centroid].begin(), tree[centroid].end());
        
        for (auto v : neighbors) {
            tree[centroid].erase(v);
            tree[v].erase(centroid);
            build(v, centroid);
        }
    };

    if (n > 0) {
        build(0, -1);
    }

    return dad;
}
