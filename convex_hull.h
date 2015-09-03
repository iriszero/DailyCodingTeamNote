//
//  convex_hull.h
//  0903
//
//  Created by IRIS on 9/3/15.
//

#ifndef _convex_hull_h
#define _convex_hull_h
#endif

#include <vector>
#define lld long long int
using namespace std;

struct Point {
    int x, y;
    
    bool operator <(const Point&p) const{
        return y>p.y || (y==p.y && x<p.x);
        
    }
};

lld outer_product (const Point& O, const Point& A, const Point &B) {
    
    return (lld)(A.x - O.x)*(B.y - O.y) - (lld)(A.y  - O.y) * (B.x - O.x);
}

vector<Point> convex_hull(vector<Point> P) {
    /*
    param:: vector of Point with x,y coordinates in long long int, P.size >= 3
    return:: convex_hull with x, y coordinates in long long int
     the first and the last element is SAME
     */
    
    int n = (int)P.size(), k=0;
    vector<Point> H(2*n);
    sort(P.begin(), P.end());
    //Lower
    for (auto now: P) {
        while(k>=2 && outer_product(H[k-2], H[k-1], now) >=0) k--;
        H[k++] = now;
    }
    //Upper
    for (int i=n-2, t=k+1; i>=0; i--) {
        while(k>=t && outer_product(H[k-2], H[k-1], P[i]) >=0)k--;
        H[k++] = P[i];
    }
    H.resize(k);
    return H;
}
