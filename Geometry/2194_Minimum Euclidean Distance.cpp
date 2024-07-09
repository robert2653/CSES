#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template<class T>
struct Point {
    T x;
    T y;
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}
    
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(const Point &p) & {
        x += p.x;
        y += p.y;
        return *this;
    }
    Point &operator-=(const Point &p) & {
        x -= p.x;
        y -= p.y;
        return *this;
    }
    Point &operator*=(const T &v) & {
        x *= v;
        y *= v;
        return *this;
    }
    Point &operator/=(const T &v) & {
        x /= v;
        y /= v;
        return *this;
    }
    Point operator-() const {
        return Point(-x, -y);
    }
    friend Point operator+(Point a, const Point &b) {
        return a += b;
    }
    friend Point operator-(Point a, const Point &b) {
        return a -= b;
    }
    friend Point operator*(Point a, const T &b) {
        return a *= b;
    }
    friend Point operator/(Point a, const T &b) {
        return a /= b;
    }
    friend Point operator*(const T &a, Point b) {
        return b *= a;
    }
    friend bool operator==(const Point &a, const Point &b) {
        return a.x == b.x && a.y == b.y;
    }
    friend istream &operator>>(istream &is, Point &p) {
        return is >> p.x >> p.y;
    }
    friend ostream &operator<<(ostream &os, const Point &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};

template<class T>
T dot(const Point<T> &a, const Point<T> &b) {
    return a.x * b.x + a.y * b.y;
}
 
template<class T>
T cross(const Point<T> &a, const Point<T> &b) {
    return a.x * b.y - a.y * b.x;
}
 
template<class T>
T square(const Point<T> &p) {
    return dot(p, p);
}

using P = Point<i64>;

template<class T>
T distanceSquare(const Point<T> &a, const Point<T> &b) {
    return square(a - b);
}

void solve() {
    int n;
    cin >> n;
    constexpr i64 inf = 8e18;
    
    vector<Point<i64>> a(n);
    for (int i = 0; i < n; i++) {
        i64 x, y;
        cin >> x >> y;
        a[i] = Point<i64>(x, y);
    }
    
    struct sortY {
        bool operator()(const Point<i64> &a, const Point<i64> &b) const {
            return a.y < b.y;
        }
    };

    struct sortXY {
        bool operator()(const Point<i64> &a, const Point<i64> &b) const {
            if (a.x == b.x) return a.y < b.y;
            else return a.x < b.x;
        }
    };

    sort(a.begin(), a.end(), sortXY());

    vector<Point<i64>> t(n);
    auto devide = [&](auto &&self, int l, int r) -> i64 {
        if (l == r) return inf;
        int m = (l + r) / 2;	
        i64 ans = min(self(self, l, m), self(self, m + 1, r));
        i64 midval = a[m].x;
        i64 p = 0;
    
        for (int i = l; i <= r; i++) {
            if ((midval - a[i].x) * (midval - a[i].x) <= ans) {
                t[p++] = a[i];
            }
        }
        sort(t.begin(), t.begin() + p, sortY());
        
        for (int i = 0; i < p; i++){
            for (int j = i + 1; j < p; j++) {
                ans = min(ans, distanceSquare(t[i], t[j]));
                if ((t[i].y - t[j].y) * (t[i].y - t[j].y) > ans) break;
            } 
        }
        return ans;
    };
    cout << devide(devide, 0, n - 1) << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}