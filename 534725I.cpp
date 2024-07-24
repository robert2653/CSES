#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
using namespace std;
using ll = long long;

struct D {
    double x;
    constexpr static double eps = 1e-12;
    D() : x{0.0} {}
    D(double v) : x{v} {}
    double val() const { return x; }
    explicit operator double() const { return x; }
    D operator-() const {
        return D(-x);
    }
    D &operator+=(const D &rhs) & {
        x += rhs.x; return *this;
    }
    D &operator-=(const D &rhs) & {
        x -= rhs.x; return *this;
    }
    D &operator*=(const D &rhs) & {
        x *= rhs.x; return *this;
    }
    D &operator/=(const D &rhs) & {
        assert(fabs(rhs.x) > eps);
        x /= rhs.x; return *this;
    }
    friend D operator+(D lhs, const D &rhs) {
        return lhs += rhs;
    }
    friend D operator-(D lhs, const D &rhs) {
        return lhs -= rhs;
    }
    friend D operator*(D lhs, const D &rhs) {
        return lhs *= rhs;
    }
    friend D operator/(D lhs, const D &rhs) {
        return lhs /= rhs;
    }
    friend bool operator<(const D &lhs, const D &rhs) {
        return lhs.x - rhs.x < -eps;
    }
    friend bool operator>(const D &lhs, const D &rhs) {
        return lhs.x - rhs.x > eps;
    }
    friend bool operator==(const D &lhs, const D &rhs) {
        return fabs(lhs.x - rhs.x) < eps;
    }
    friend bool operator<=(const D &lhs, const D &rhs) {
        return lhs < rhs || lhs == rhs;
    }
    friend bool operator>=(const D &lhs, const D &rhs) {
        return lhs > rhs || lhs == rhs;
    }
    friend bool operator!=(const D &lhs, const D &rhs) {
        return !(lhs == rhs);
    }
    friend istream &operator>>(istream &is, D &a) {
        double v; is >> v; a = D(v); return is;
    }
    friend ostream &operator<<(ostream &os, const D &a) {
        return os << fixed << setprecision(10) << a.val()
        + (a.val() > 0 ? eps : a.val() < 0 ? -eps : 0);
    } // eps should < precision
};

template<class T>
struct Point {
    T x, y;
    Point(const T &x_ = 0, const T &y_ = 0) : x(x_), y(y_) {}
    template<class U>
    operator Point<U>() {
        return Point<U>(U(x), U(y));
    }
    Point &operator+=(const Point &p) & {
        x += p.x; y += p.y; return *this;
    }
    Point &operator-=(const Point &p) & {
        x -= p.x; y -= p.y; return *this;
    }
    Point &operator*=(const T &v) & {
        x *= v; y *= v; return *this;
    }
    Point &operator/=(const T &v) & {
        x /= v; y /= v; return *this;
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
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
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
template<class T>
double length(const Point<T> &p) {
    return sqrt(double(square(p)));
}
template<class T>
double length(const Line<T> &l) {
    return length(l.a - l.b);
}
template<class T>
Point<T> rotate(const Point<T> &a) {
    return Point(-a.y, a.x);
}
template<class T>
Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}
template<class T>
pair<T, Point<T>> MinCircular(vector<Point<T>> &a) {
    random_shuffle(a.begin(), a.end());
    int n = a.size();
    Point<T> c = a[0]; T r = 0;
    for (int i = 1; i < n; i++) {
        if (T(length(c - a[i]) - r) > 0.0) {
            c = a[i], r = 0;
            for (int j = 0; j < i; j++) {
                if (T(length(c - a[j]) - r) > 0.0) {
                    c = (a[i] + a[j]) / 2.0;
                    r = length(c - a[i]);
                    for (int k = 0; k < j; k++) {
                        if (T(length(c - a[k]) - r) > 0.0) {
                            Point<T> p = (a[j] + a[i]) / 2;
                            Point<T> q = (a[j] + a[k]) / 2;
                            c = lineIntersection(Line(p, p + rotate(a[j] - a[i])), Line(q, q + rotate(a[k] - a[j])));
                            r = length(c - a[i]);
                        }
                    }
                }
            }
        }
    }
    return make_pair(r, c);
}

using P = Point<D>;
void solve() {
    int n, R, r;
    cin >> n >> R >> r;
    vector<P> a(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i + 1];
        a[i + 1] = a[i] + a[i + 1];
    }
    auto res = MinCircular(a).second;
    cout << -res.x << " " << -res.y << "\n";
}

int main() {
    freopen("robots.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}