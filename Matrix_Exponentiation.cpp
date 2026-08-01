#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
