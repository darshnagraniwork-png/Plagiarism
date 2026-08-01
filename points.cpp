#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <cfloat>

struct Point {
    double x, y;
};

bool compareX(const Point& a, const Point& b) {
    return a.x < b.x;
}

bool compareY(const Point& a, const Point& b) {
    return a.y < b.y;
}

double dist(const Point& p1, const Point& p2) {
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}

double bruteForce(const std::vector<Point>& P, int left, int right) {
    double minDist = DBL_MAX;
    for (int i = left; i < right; ++i) {
        for (int j = i + 1; j <= right; ++j) {
            minDist = std::min(minDist, dist(P[i], P[j]));
        }
    }
    return minDist;
}

double stripClosest(std::vector<Point>& strip, double d) {
    double minDist = d;  

    std::sort(strip.begin(), strip.end(), compareY);

    
    for (size_t i = 0; i < strip.size(); ++i) {
        for (size_t j = i + 1; j < strip.size() && (strip[j].y - strip[i].y) < minDist; ++j) {
            minDist = std::min(minDist, dist(strip[i], strip[j]));
        }
    }
    return minDist;
}


double closestUtil(const std::vector<Point>& Px, int left, int right) {
    
    if (right - left <= 2) {
        return bruteForce(Px, left, right);
    }

    int mid = left + (right - left) / 2;
    Point midPoint = Px[mid];

    double dl = closestUtil(Px, left, mid);
    double dr = closestUtil(Px, mid + 1, right);

    double d = std::min(dl, dr);

    
    std::vector<Point> strip;
    for (int i = left; i <= right; ++i) {
        if (std::abs(Px[i].x - midPoint.x) < d) {
            strip.push_back(Px[i]);
        }
    }

    
    return std::min(d, stripClosest(strip, d));
}

double closest(std::vector<Point> P) {
    
    std::sort(P.begin(), P.end(), compareX);

    return closestUtil(P, 0, P.size() - 1);
}


