#include <iostream>
#include <cmath>
#include <algorithm>


const double EPS = 1e-9;

struct Point {
    double x, y;
};

double crossProduct(const Point& A, const Point& B, const Point& C) {
    return (B.x - A.x) * (C.y - A.y) - (B.y - A.y) * (C.x - A.x);
}

bool onSegment(const Point& A, const Point& B, const Point& P) {
    return P.x >= std::min(A.x, B.x) - EPS && P.x <= std::max(A.x, B.x) + EPS &&
           P.y >= std::min(A.y, B.y) - EPS && P.y <= std::max(A.y, B.y) + EPS;
}


bool lineSegmentIntersect(const Point& L1, const Point& L2, const Point& S1, const Point& S2) {
    
    double cross1 = crossProduct(L1, L2, S1);
    double cross2 = crossProduct(L1, L2, S2);

    
    if ((cross1 > EPS && cross2 < -EPS) || (cross1 < -EPS && cross2 > EPS)) {
        return true;
    }

    
    if (std::abs(cross1) <= EPS && onSegment(L1, L2, S1)) return true;
    if (std::abs(cross2) <= EPS && onSegment(L1, L2, S2)) return true;

    
    if (std::abs(cross1) <= EPS && std::abs(cross2) <= EPS) {
        return onSegment(S1, S2, L1) || onSegment(S1, S2, L2) || 
               onSegment(L1, L2, S1) || onSegment(L1, L2, S2);
    }

    return false;
}


