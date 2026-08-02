#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <functional>

using namespace std;

vector<vector<int>> getSCCs(const vector<vector<int>>& adj) {
    int n = adj.size();
    vector<int> disc(n, -1);
    vector<int> low(n, -1);
    vector<bool> inSt(n, false);
    stack<int> st;
    int timer = 0;
    vector<vector<int>> allSCCs;

    function<void(int)> findSCC = [&](int u) {
        disc[u] = low[u] = ++timer;
        st.push(u);
        inSt[u] = true;

        for (int v : adj[u]) {
            if (disc[v] == -1) {
                findSCC(v);
                low[u] = min(low[u], low[v]);
            } else if (inSt[v]) {
                low[u] = min(low[u], disc[v]);
            }
        }

        if (low[u] == disc[u]) {
            vector<int> scc;
            while (true) {
                int x = st.top();
                st.pop();
                inSt[x] = false;
                scc.push_back(x);
                if (x == u) break;
            }
            allSCCs.push_back(scc);
        }
    };

    for (int i = 0; i < n; i++) {
        if (disc[i] == -1) {
            findSCC(i);
        }
    }

    return allSCCs;
}
