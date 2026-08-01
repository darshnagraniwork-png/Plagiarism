#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

void treeDP(int u, int p, const vector<vector<int>>& adj, vector<int>& dpIn, vector<int>& dpEx) {
    dpIn[u] = 1;
    dpEx[u] = 0;
    for (int v : adj[u]) {
        if (v == p) continue;
        treeDP(v, u, adj, dpIn, dpEx);
        dpIn[u] += dpEx[v];
        dpEx[u] += max(dpIn[v], dpEx[v]);
    }
}
