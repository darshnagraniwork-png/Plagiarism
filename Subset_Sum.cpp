#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
