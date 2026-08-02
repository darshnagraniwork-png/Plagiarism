#include <iostream>
#include <vector>
#include <stack>
#include <functional>

using namespace std;

void topologicalSort(int V, const vector<vector<int>>& adj) {
    stack<int> Stack;
    vector<bool> visited(V, false);

    function<void(int)> dfs = [&](int v) {
        visited[v] = true;
        for (int u : adj[v]) {
            if (!visited[u]) {
                dfs(u);
            }
        }
        Stack.push(v);
    };

    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs(i);
        }
    }

    while (!Stack.empty()) {
        cout << Stack.top() << " ";
        Stack.pop();
    }
}
