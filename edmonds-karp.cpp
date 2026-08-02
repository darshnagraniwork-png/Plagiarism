#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>

using namespace std;

long long edmondsKarp(int n, int s, int t, const vector<vector<long long>>& edges) {
    vector<vector<long long>> capacity(n, vector<long long>(n, 0));
    vector<vector<int>> adj(n);

    for (const auto& edge : edges) {
        int u = (int)edge[0];
        int v = (int)edge[1];
        long long cap = edge[2];
        
        if (capacity[u][v] == 0 && capacity[v][u] == 0) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
        capacity[u][v] += cap;
    }

    long long max_flow = 0;
    vector<int> parent(n);

    auto bfs = [&]() {
        fill(parent.begin(), parent.end(), -1);
        parent[s] = -2;
        queue<pair<int, long long>> q;
        q.push({s, LLONG_MAX});

        while (!q.empty()) {
            int cur = q.front().first;
            long long flow = q.front().second;
            q.pop();

            for (int next : adj[cur]) {
                if (parent[next] == -1 && capacity[cur][next] > 0) {
                    parent[next] = cur;
                    long long new_flow = min(flow, capacity[cur][next]);
                    
                    if (next == t) {
                        return new_flow;
                    }
                    q.push({next, new_flow});
                }
            }
        }
        return 0LL;
    };

    long long flow;
    while ((flow = bfs()) > 0) {
        max_flow += flow;
        int cur = t;
        while (cur != s) {
            int prev = parent[cur];
            capacity[prev][cur] -= flow;
            capacity[cur][prev] += flow;
            cur = prev;
        }
    }

    return max_flow;
}
