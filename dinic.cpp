#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
#include <functional>

using namespace std;

long long dinicMaxFlow(int n, int s, int t, const vector<vector<long long>>& edges) {
    struct Edge {
        int to;
        long long cap;
        long long flow;
        int rev;
    };

    vector<vector<Edge>> adj(n);
    for (const auto& e : edges) {
        adj[e[0]].push_back({(int)e[1], e[2], 0, (int)adj[e[1]].size()});
        adj[e[1]].push_back({(int)e[0], 0, 0, (int)adj[e[0]].size() - 1});
    }

    vector<int> level(n);
    vector<int> ptr(n);

    auto bfs = [&]() {
        fill(level.begin(), level.end(), -1);
        level[s] = 0;
        queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (auto& edge : adj[v]) {
                if (edge.cap - edge.flow > 0 && level[edge.to] == -1) {
                    level[edge.to] = level[v] + 1;
                    q.push(edge.to);
                }
            }
        }
        return level[t] != -1;
    };

    function<long long(int, long long)> dfs = [&](int v, long long pushed) {
        if (pushed == 0 || v == t) return pushed;
        for (int& cid = ptr[v]; cid < adj[v].size(); ++cid) {
            auto& edge = adj[v][cid];
            int tr = edge.to;
            if (level[v] + 1 != level[tr] || edge.cap - edge.flow == 0) continue;
            long long push = dfs(tr, min(pushed, edge.cap - edge.flow));
            if (push == 0) continue;
            edge.flow += push;
            adj[tr][edge.rev].flow -= push;
            return push;
        }
        return 0LL;
    };

    long long flow = 0;
    while (bfs()) {
        fill(ptr.begin(), ptr.end(), 0);
        while (long long pushed = dfs(s, LLONG_MAX)) {
            flow += pushed;
        }
    }
    return flow;
}
