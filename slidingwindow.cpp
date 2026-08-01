#include <iostream>
#include <vector>
using namespace std;

int maxSum(vector<int>& arr, int k) {
    int n = arr.size();

    if (k > n)
        return -1;

    int windowSum = 0;

    for (int i = 0; i < k; i++)
        windowSum += arr[i];

    int maxSum = windowSum;

    for (int i = k; i < n; i++) {
        windowSum += arr[i] - arr[i - k];
        maxSum = max(maxSum, windowSum);
    }

    return maxSum;
}