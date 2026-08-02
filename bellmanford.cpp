#include <vector>

using namespace std;

const int INF = 1e9;

bool bellmanFord(int start, int n, const vector<vector<int>>& edges, vector<int>& dist) {
    dist.assign(n, INF);
    dist[start] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (const auto& edge : edges) {
            int u = edge[0];
            int v = edge[1];
            int weight = edge[2];
            
            if (dist[u] != INF && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
            }
        }
    }

    for (const auto& edge : edges) {
        int u = edge[0];
        int v = edge[1];
        int weight = edge[2];
        
        if (dist[u] != INF && dist[u] + weight < dist[v]) {
            return false;
        }
    }

    return true;
}
