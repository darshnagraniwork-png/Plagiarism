#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

int knapsack01(int W, const vector<int>& wt, const vector<int>& val, int n) {
    vector<int> dp(W + 1, 0);
    for (int i = 0; i < n; i++) {
        for (int w = W; w >= wt[i]; w--) {
            dp[w] = max(dp[w], dp[w - wt[i]] + val[i]);
        }
    }
    return dp[W];
}

int lcs(const string& text1, const string& text2) {
    int m = text1.size(), n = text2.size();
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (text1[i - 1] == text2[j - 1])
                dp[i][j] = 1 + dp[i - 1][j - 1];
            else
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
        }
    }
    return dp[m][n];
}

int lis(const vector<int>& nums) {
    vector<int> sub;
    for (int x : nums) {
        auto it = lower_bound(sub.begin(), sub.end(), x);
        if (it == sub.end())
            sub.push_back(x);
        else
            *it = x;
    }
    return sub.size();
}

bool isSubsetSum(const vector<int>& arr, int sum) {
    int n = arr.size();
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for (int num : arr) {
        for (int j = sum; j >= num; j--) {
            if (dp[j - num]) dp[j] = true;
        }
    }
    return dp[sum];
}

vector<vector<long long>> multiplyMatrix(const vector<vector<long long>>& A, const vector<vector<long long>>& B, long long mod) {
    int n = A.size();
    vector<vector<long long>> C(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            for (int j = 0; j < n; j++) {
                C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
            }
        }
    }
    return C;
}

vector<vector<long long>> powerMatrix(vector<vector<long long>> A, long long p, long long mod) {
    int n = A.size();
    vector<vector<long long>> res(n, vector<long long>(n, 0));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    while (p > 0) {
        if (p & 1) res = multiplyMatrix(res, A, mod);
        A = multiplyMatrix(A, A, mod);
        p >>= 1;
    }
    return res;
}

int bitmaskTSP(const vector<vector<int>>& dist) {
    int n = dist.size();
    vector<vector<int>> dp(1 << n, vector<int>(n, 1e9));
    dp[1][0] = 0;
    for (int mask = 1; mask < (1 << n); mask++) {
        for (int u = 0; u < n; u++) {
            if (!(mask & (1 << u))) continue;
            for (int v = 0; v < n; v++) {
                if (mask & (1 << v)) continue;
                dp[mask | (1 << v)][v] = min(dp[mask | (1 << v)][v], dp[mask][u] + dist[u][v]);
            }
        }
    }
    return dp[(1 << n) - 1][0];
}

long long solveDigitDP(const string& S) {
    int n = S.size();
    long long dp[20][2][200];
    auto solve = [&](auto& self, int idx, bool tight, int sum) -> long long {
        if (idx == n) return sum;
        if (dp[idx][tight][sum] != -1) return dp[idx][tight][sum];
        int limit = tight ? (S[idx] - '0') : 9;
        long long ans = 0;
        for (int d = 0; d <= limit; d++) {
            ans += self(self, idx + 1, tight && (d == limit), sum + d);
        }
        return dp[idx][tight][sum] = ans;
    };
    for (int i = 0; i < 20; i++)
        for (int j = 0; j < 2; j++)
            for (int k = 0; k < 200; k++) dp[i][j][k] = -1;
    return solve(solve, 0, true, 0);
}

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

struct ConvexHullTrick {
    struct Line {
        long long m, b;
        long long eval(long long x) const { return m * x + b; }
    };
    deque<Line> hull;
    bool bad(const Line& l1, const Line& l2, const Line& l3) {
        return (double)(l3.b - l1.b) / (l1.m - l3.m) <= (double)(l2.b - l1.b) / (l1.m - l2.m);
    }
    void addLine(long long m, long long b) {
        Line l = {m, b};
        while (hull.size() >= 2 && bad(hull[hull.size() - 2], hull.back(), l))
            hull.pop_back();
        hull.push_back(l);
    }
    long long query(long long x) {
        while (hull.size() >= 2 && hull[0].eval(x) <= hull[1].eval(x))
            hull.pop_front();
        return hull[0].eval(x);
    }
};

struct LiChaoTree {
    struct Line {
        long long m, b;
        long long eval(long long x) const { return m * x + b; }
    };
    int L, R;
    Line line;
    LiChaoTree *left = nullptr, *right = nullptr;

    LiChaoTree(int l, int r) : L(l), R(r), line({0, (long long)1e18}) {}

    void insert(Line newLine) {
        int mid = L + (R - L) / 2;
        bool leftBetter = newLine.eval(L) < line.eval(L);
        bool midBetter = newLine.eval(mid) < line.eval(mid);

        if (midBetter) swap(line, newLine);

        if (L == R) return;

        if (leftBetter != midBetter) {
            if (!left) left = new LiChaoTree(L, mid);
            left->insert(newLine);
        } else {
            if (!right) right = new LiChaoTree(mid + 1, R);
            right->insert(newLine);
        }
    }

    long long query(int x) {
        if (L == R) return line.eval(x);
        int mid = L + (R - L) / 2;
        long long res = line.eval(x);
        if (x <= mid && left) res = min(res, left->query(x));
        else if (x > mid && right) res = min(res, right->query(x));
        return res;
    }
};