#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
