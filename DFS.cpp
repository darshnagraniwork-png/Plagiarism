#include <vector>
#include <functional>

using namespace std;

void dfs(int start, int n, const vector<vector<int>>& adj, vector<int>& result) {
    vector<bool> visited(n, false);

    function<void(int)> dfs_util = [&](int u) {
        visited[u] = true;
        result.push_back(u);

        for (int v : adj[u]) {
            if (!visited[v]) {
                dfs_util(v);
            }
        }
    };

    dfs_util(start);
}
