#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

struct Query {
    int left, right, index;
};

int blockSize;

bool compare(Query a, Query b) {
    if (a.left / blockSize != b.left / blockSize)
        return a.left < b.left;

    return a.right < b.right;
}

vector<int> mosAlgorithm(vector<int>& arr, vector<Query>& queries) {
    blockSize = sqrt(arr.size());

    sort(queries.begin(), queries.end(), compare);

    vector<int> answer(queries.size());

    int currentLeft = 0;
    int currentRight = -1;
    int currentSum = 0;

    for (Query q : queries) {

        while (currentLeft > q.left)
            currentSum += arr[--currentLeft];

        while (currentRight < q.right)
            currentSum += arr[++currentRight];

        while (currentLeft < q.left)
            currentSum -= arr[currentLeft++];

        while (currentRight > q.right)
            currentSum -= arr[currentRight--];

        answer[q.index] = currentSum;
    }

    return answer;
}