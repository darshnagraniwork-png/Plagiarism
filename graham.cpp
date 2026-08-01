#include <iostream>
#include <vector>
#include <algorithm>
#include <stack>


struct Point {
    int x, y;

    
    bool operator<(const Point& other) const {
        if (y != other.y) return y < other.y;
        return x < other.x;
    }
};


Point pivot;


long long distSq(Point p1, Point p2) {
    long long dx = p1.x - p2.x;
    long long dy = p1.y - p2.y;
    return dx * dx + dy * dy;
}

int orientation(Point a, Point b, Point c) {
    long long val = (long long)(b.y - a.y) * (c.x - b.x) - 
                    (long long)(b.x - a.x) * (c.y - b.y);
    if (val == 0) return 0; 
    return (val > 0) ? 1 : -1; 
}

bool comparePolar(Point p1, Point p2) {
    int orient = orientation(pivot, p1, p2);
    if (orient == 0) {
        
        return distSq(pivot, p1) < distSq(pivot, p2);
    }
    
    return (orient == -1);
}

Point nextToTop(std::stack<Point>& S) {
    Point p = S.top();
    S.pop();
    Point res = S.top();
    S.push(p);
    return res;
}

std::vector<Point> grahamScan(std::vector<Point> points) {
    int n = points.size();
    std::vector<Point> hull;

    
    if (n < 3) return points;

    
    int min_idx = 0;
    for (int i = 1; i < n; i++) {
        if (points[i] < points[min_idx]) {
            min_idx = i;
        }
    }

    
    std::swap(points[0], points[min_idx]);
    pivot = points[0];

    
    std::sort(points.begin() + 1, points.end(), comparePolar);

    
    int m = 1; 
    for (int i = 1; i < n; i++) {
        
        while (i < n - 1 && orientation(pivot, points[i], points[i + 1]) == 0) {
            i++;
        }
        points[m] = points[i];
        m++;
    }

    
    if (m < 3) return hull;

    
    std::stack<Point> S;
    S.push(points[0]);
    S.push(points[1]);
    S.push(points[2]);

    for (int i = 3; i < m; i++) {
        
        while (S.size() > 1 && orientation(nextToTop(S), S.top(), points[i]) != -1) {
            S.pop();
        }
        S.push(points[i]);
    }

    
    while (!S.empty()) {
        hull.push_back(S.top());
        S.pop();
    }
    
    
    std::reverse(hull.begin(), hull.end());
    return hull;
}


