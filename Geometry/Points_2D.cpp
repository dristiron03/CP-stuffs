#include<bits/stdc++.h>
using namespace std;

#define ll long long
struct point2d {
    ll x, y;
    point2d() {}
    point2d(ll x, ll y): x(x), y(y) {}
    point2d& operator+=(const point2d &t) {
        //Adding two vectors
        x += t.x;
        y += t.y;
        return *this;
    }
    point2d& operator-=(const point2d &t) {
        // Subtracting two vectors
        x -= t.x;
        y -= t.y;
        return *this;
    }
    point2d& operator*=(ll t) {
        // Multiplying a vector by a scaler
        x *= t;
        y *= t;
        return *this;
    }
    point2d& operator/=(ll t) {
        // Dividing a vector by a scaler
        x /= t;
        y /= t;
        return *this;
    }
    point2d operator+(const point2d &t) const {
        return point2d(*this) += t;
    }
    point2d operator-(const point2d &t) const {
        return point2d(*this) -= t;
    }
    point2d operator*(ll t) const {
        return point2d(*this) *= t;
    }
    point2d operator/(ll t) const {
        return point2d(*this) /= t;
    }
};
point2d operator*(ll a, point2d b) {
    return b * a;
}
ll dot(point2d a, point2d b) {
    return a.x * b.x + a.y * b.y;
}
ll norm(point2d a) {
    return dot(a, a);
}
long double abs(point2d a) {
    return sqrt(norm(a));
}
long double proj(point2d a, point2d b) {
    return dot(a, b) / abs(b);
}
long double angle(point2d a, point2d b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
ll cross(point2d a, point2d b){
    return a.x*b.y-a.y*b.x;
}
point2d intersect(point2d a1, point2d d1, point2d a2, point2d d2) {
    return a1 + cross(a2 - a1, d2) / cross(d1, d2) * d1;
}