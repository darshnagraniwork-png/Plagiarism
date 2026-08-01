#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
