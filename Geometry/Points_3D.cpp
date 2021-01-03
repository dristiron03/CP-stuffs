#include<bits/stdc++.h>
using namespace std;
#define ll long long
struct point3d {
    ll x, y, z;
    point3d() {}
    point3d(ll x, ll y, ll z): x(x), y(y), z(z) {}
    point3d& operator+=(const point3d &t) {
        x += t.x;
        y += t.y;
        z += t.z;
        return *this;
    }
    point3d& operator-=(const point3d &t) {
        x -= t.x;
        y -= t.y;
        z -= t.z;
        return *this;
    }
    point3d& operator*=(ll t) {
        x *= t;
        y *= t;
        z *= t;
        return *this;
    }
    point3d& operator/=(ll t) {
        x /= t;
        y /= t;
        z /= t;
        return *this;
    }
    point3d operator+(const point3d &t) const {
        return point3d(*this) += t;
    }
    point3d operator-(const point3d &t) const {
        return point3d(*this) -= t;
    }
    point3d operator*(ll t) const {
        return point3d(*this) *= t;
    }
    point3d operator/(ll t) const {
        return point3d(*this) /= t;
    }
};
point3d operator*(ll a, point3d b) {
    return b * a;
}
ll dot(point3d a, point3d b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}
ll norm(point3d a) {
    return dot(a, a);
}
long double abs(point3d a) {
    return sqrt(norm(a));
}
long double proj(point3d a, point3d b) {
    return dot(a, b) / abs(b);
}
long double angle(point3d a, point3d b) {
    return acos(dot(a, b) / abs(a) / abs(b));
}
point3d cross(point3d a, point3d b) {
    return point3d(a.y * b.z - a.z * b.y,
                   a.z * b.x - a.x * b.z,
                   a.x * b.y - a.y * b.x);
}
ll triple(point3d a, point3d b, point3d c) {
    return dot(a, cross(b, c));
}
