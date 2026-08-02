#include <iostream>
#include <vector>
#include <set>
#include <functional>
#include <utility>

using namespace std;

pair<vector<int>, vector<pair<int, int>>> findAPsAndBridges(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<int> tin(V, -1);
    vector<int> low(V, -1);
    int timer = 0;
    
    set<int> ap_set;
    vector<pair<int, int>> bridges;
    
    function<void(int, int)> dfs = [&](int u, int p) {
        visited[u] = true;
        tin[u] = low[u] = ++timer;
        int children = 0;
        
        for (int v : adj[u]) {
            if (v == p) continue;
            
            if (visited[v]) {
                low[u] = min(low[u], tin[v]);
            } else {
                children++;
                dfs(v, u);
                low[u] = min(low[u], low[v]);
                
                if (low[v] > tin[u]) {
                    bridges.push_back({u, v});
                }
                
                if (low[v] >= tin[u] && p != -1) {
                    ap_set.insert(u);
                }
            }
        }
        
        if (p == -1 && children > 1) {
            ap_set.insert(u);
        }
    };
    
    for (int i = 0; i < V; ++i) {
        if (!visited[i]) {
            dfs(i, -1);
        }
    }
    
    vector<int> articulation_points(ap_set.begin(), ap_set.end());
    return {articulation_points, bridges};
}
