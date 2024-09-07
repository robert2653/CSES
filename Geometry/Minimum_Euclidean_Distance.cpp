#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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
Point<T> normalize(const Point<T> &p) {
    return p / length(p);
}
template<class T>
Point<T> rotate(const Point<T> &a) {
    return Point(-a.y, a.x);
}
template<class T>
int sgn(const Point<T> &a) {
    return a.y > 0 || (a.y == 0 && a.x > 0) ? 1 : -1;
}

template<class T>
struct Line {
    Point<T> a;
    Point<T> b;
    Line(const Point<T> &a_ = Point<T>(), const Point<T> &b_ = Point<T>()) : a(a_), b(b_) {}
};
template<class T>
double length(const Line<T> &l) {
    return length(l.a - l.b);
}
template<class T>
bool parallel(const Line<T> &l1, const Line<T> &l2) {
    return cross(l1.b - l1.a, l2.b - l2.a) == 0;
}
template<class T>
double distance(const Point<T> &a, const Point<T> &b) {
    return length(a - b);
}
template<class T>
double distancePL(const Point<T> &p, const Line<T> &l) {
    return abs(cross(l.a - l.b, l.a - p)) / length(l);
}
template<class T>
double distancePS(const Point<T> &p, const Line<T> &l) {
    if (dot(p - l.a, l.b - l.a) < 0)
        return distance(p, l.a);
    if (dot(p - l.b, l.a - l.b) < 0)
        return distance(p, l.b);
    return distancePL(p, l);
}
template<class T>
bool pointOnLineLeft(const Point<T> &p, const Line<T> &l) {
    return cross(l.b - l.a, p - l.a) > 0;
}
template<class T>
Point<T> lineIntersection(const Line<T> &l1, const Line<T> &l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}
template<class T>
bool pointOnSegment(const Point<T> &p, const Line<T> &l) {
    return cross(p - l.a, l.b - l.a) == 0 && min(l.a.x, l.b.x) <= p.x && p.x <= max(l.a.x, l.b.x)
        && min(l.a.y, l.b.y) <= p.y && p.y <= max(l.a.y, l.b.y);
}
template<class T>
bool pointInPolygon(const Point<T> &a, const vector<Point<T>> &p) {
    int n = p.size(), t = 0;
    for (int i = 0; i < n; i++) {
        if (pointOnSegment(a, Line(p[i], p[(i + 1) % n]))) {
            return true;
        }
    }
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, Line(v, u)))
            t ^= 1;
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, Line(u, v)))
            t ^= 1;
    }
    return t == 1;
}
// 0 : not inside
// 1 : on boundary
// 2 : strictly inside
template<class T>
int pointInConvexPolygon(const Point<T> &a, const vector<Point<T>> &p) {
    int n = p.size();
    if (n == 0) {
        return 0;
    } else if (n == 1) {
        return a == p[0];
    }
    if (pointOnSegment(a, Line(p[0], p[1])) || pointOnSegment(a, Line(p[0], p[n - 1]))) {
        return 1;
    } else if (pointOnLineLeft(a, Line(p[1], p[0])) || pointOnLineLeft(a, Line(p[0], p[n - 1]))) {
        return 0;
    }
    int lo = 1, hi = n - 2;
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        if (pointOnLineLeft(a, Line(p[0], p[x]))) {
            lo = x;
        } else {
            hi = x - 1;
        }
    }
    if (pointOnLineLeft(a, Line(p[lo], p[lo + 1]))) {
        return 2;
    } else {
        return pointOnSegment(a, Line(p[lo], p[lo + 1]));
    }
}
template<class T>
bool lineIntersectsPolygon(const Line<T> &l, const vector<Point<T>> &p) {
    int n = p.size();
    Point<T> a = l.a, b = l.b;
    for (int i = 0; i < n; i++) {
        Line<T> seg(p[i], p[(i + 1) % n]);
        if (cross(b - a, seg.a - a) == 0 || cross(b - a, seg.b - a) == 0) {
            return true;
        }
        if (cross(b - a, seg.a - a) > 0 ^ cross(b - a, seg.b - a) > 0) {
            return true;
        }
    }
    return false;
}
// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
template<class T>
tuple<int, Point<T>, Point<T>> segmentIntersection(const Line<T> &l1, const Line<T> &l2) {
    if (max(l1.a.x, l1.b.x) < min(l2.a.x, l2.b.x))
        return {0, Point<T>(), Point<T>()};
    if (min(l1.a.x, l1.b.x) > max(l2.a.x, l2.b.x))
        return {0, Point<T>(), Point<T>()};
    if (max(l1.a.y, l1.b.y) < min(l2.a.y, l2.b.y))
        return {0, Point<T>(), Point<T>()};
    if (min(l1.a.y, l1.b.y) > max(l2.a.y, l2.b.y))
        return {0, Point<T>(), Point<T>()};
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, Point<T>(), Point<T>()};
        } else {
            auto maxx1 = max(l1.a.x, l1.b.x);
            auto minx1 = min(l1.a.x, l1.b.x);
            auto maxy1 = max(l1.a.y, l1.b.y);
            auto miny1 = min(l1.a.y, l1.b.y);
            auto maxx2 = max(l2.a.x, l2.b.x);
            auto minx2 = min(l2.a.x, l2.b.x);
            auto maxy2 = max(l2.a.y, l2.b.y);
            auto miny2 = min(l2.a.y, l2.b.y);
            Point<T> p1(max(minx1, minx2), max(miny1, miny2));
            Point<T> p2(min(maxx1, maxx2), min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1))
                swap(p1.y, p2.y);
            if (p1 == p2) {
                return {3, p1, p2};
            } else {
                return {2, p1, p2};
            }
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0))
        return {0, Point<T>(), Point<T>()};
    Point p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) {
        return {1, p, p};
    } else {
        return {3, p, p};
    }
}
template<class T>
double distanceSS(const Line<T> &l1, const Line<T> &l2) {
    if (get<0>(segmentIntersection(l1, l2)) != 0)
        return 0.0;
    return min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}
template<class T>
bool segmentInPolygon(const Line<T> &l, const vector<Point<T>> &p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) return false;
    if (!pointInPolygon(l.b, p)) return false;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, Line(u, v));
        if (t == 1) return false;
        if (t == 0) continue;
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b)
                if (cross(v - u, w - v) > 0)
                    return false;
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, Line(v, u))
                    || pointOnLineLeft(l.b, Line(v, u)))
                    return false;
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l)
                            && pointOnLineLeft(w, Line(u, v)))
                            return false;
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v)))
                            return false;
                    }
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, Line(l.b, l.a))) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            && pointOnLineLeft(w, Line(u, v)))
                            return false;
                    } else {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v)))
                            return false;
                    }
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, Line(l.b, l.a))
                            || pointOnLineLeft(w, Line(u, v)))
                            return false;
                    } else {
                        if (pointOnLineLeft(w, l)
                            || pointOnLineLeft(w, Line(u, v)))
                            return false;
                    }
                }
            }
        }
    }
    return true;
}
template<class T>
vector<Point<T>> convexHull(vector<Point<T>> a) {
    sort(a.begin(), a.end(), [](const Point<T> &l, const Point<T> &r) {
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    });
    a.resize(unique(a.begin(), a.end()) - a.begin());
    if (a.size() <= 1) return a;
    vector<Point<T>> h(a.size() + 1);
    int s = 0, t = 0;
    for (int i = 0; i < 2; i++, s = --t) {
        for (Point<T> p : a) {
            while (t >= s + 2 && cross(h[t - 1] - h[t - 2], p - h[t - 2]) <= 0) t--;
            h[t++] = p;
        }
        reverse(a.begin(), a.end());
    }
    return {h.begin(), h.begin() + t};
}
template<class T>
vector<Point<T>> hp(vector<Line<T>> lines) {
    sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        if (sgn(d1) != sgn(d2))
            return sgn(d1) == 1;
        return cross(d1, d2) > 0;
    });
    deque<Line<T>> ls;
    deque<Point<T>> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l))
            ps.pop_back(), ls.pop_back();
        while (!ps.empty() && !pointOnLineLeft(ps[0], l))
            ps.pop_front(), ls.pop_front();
        if (cross(l.b - l.a, ls.back().b - ls.back().a) == 0) {
            if (dot(l.b - l.a, ls.back().b - ls.back().a) > 0) {
                if (!pointOnLineLeft(ls.back().a, l)) {
                    assert(ls.size() == 1);
                    ls[0] = l;
                }
                continue;
            }
            return {};
        }
        ps.push_back(lineIntersection(ls.back(), l));
        ls.push_back(l);
    }
    while (!ps.empty() && !pointOnLineLeft(ps.back(), ls[0]))
        ps.pop_back(), ls.pop_back();
    if (ls.size() <= 2) return {};
    ps.push_back(lineIntersection(ls[0], ls.back()));
    return vector(ps.begin(), ps.end());
}
using P = Point<ll>;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    constexpr ll inf = 8E18;
    vector<Point<ll>> a(n);
    for (int i = 0; i < n; i++) {
        ll x, y;
        cin >> x >> y;
        a[i] = Point<ll>(x, y);
    }
    struct sortY {
        bool operator()(const Point<ll> &a, const Point<ll> &b) const {
            return a.y < b.y;
        }
    };
    struct sortXY {
        bool operator()(const Point<ll> &a, const Point<ll> &b) const {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
    };
    sort(a.begin(), a.end(), sortXY());
    vector<Point<ll>> t(n);
    auto devide = [&](auto &&self, int l, int r) -> ll {
        if (l == r) return inf;
        int m = (l + r) / 2;	
        ll ans = min(self(self, l, m), self(self, m + 1, r));
        ll midval = a[m].x;
        ll p = 0;
        for (int i = l; i <= r; i++) {
            if ((midval - a[i].x) * (midval - a[i].x) <= ans) {
                t[p++] = a[i];
            }
        }
        sort(t.begin(), t.begin() + p, sortY());
        for (int i = 0; i < p; i++){
            for (int j = i + 1; j < p; j++) {
                ans = min(ans, square(t[i] - t[j]));
                if ((t[i].y - t[j].y) * (t[i].y - t[j].y) > ans) break;
            } 
        }
        return ans;
    };
    cout << devide(devide, 0, n - 1) << "\n";
    return 0;
}