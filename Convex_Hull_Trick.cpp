#include <vector>
#include <string>
#include <algorithm>
#include <cmath>
#include <climits>
#include <deque>

using namespace std;

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
