#include <iostream>
#include <vector>
#include <stack>
#include <functional>
#include <algorithm>

using namespace std;

vector<vector<int>> kosaraju(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    stack<int> st;

    function<void(int)> DFS1 = [&](int u) {
        visited[u] = true;
        for (int v : adj[u]) {
            if (!visited[v]) DFS1(v);
        }
        st.push(u);
    };

    for (int i = 0; i < V; i++) {
        if (!visited[i]) DFS1(i);
    }

    vector<vector<int>> revAdj(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            revAdj[v].push_back(u);
        }
    }

    fill(visited.begin(), visited.end(), false);
    vector<vector<int>> SCCs;

    function<void(int, vector<int>&)> DFS2 = [&](int u, vector<int>& scc) {
        visited[u] = true;
        scc.push_back(u);
        for (int v : revAdj[u]) {
            if (!visited[v]) DFS2(v, scc);
        }
    };

    while (!st.empty()) {
        int u = st.top();
        st.pop();
        if (!visited[u]) {
            vector<int> scc;
            DFS2(u, scc);
            SCCs.push_back(scc);
        }
    }

    return SCCs;
}
