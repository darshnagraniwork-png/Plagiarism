#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
