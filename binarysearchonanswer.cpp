#include <iostream>
using namespace std;

int binarySearchOnAnswer(int X) {
    int lo = 0;
    int hi = X;
    int answer = -1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;

        if (mid * mid < X) {
            answer = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }

    return answer;
}