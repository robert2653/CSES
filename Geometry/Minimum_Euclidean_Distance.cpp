#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const double eps = 1E-9;
template<class T>
struct Pt {
    T x, y;
    Pt(T x = 0, T y = 0) : x(x), y(y) {}
    Pt operator-() { return P(-x, -y); }
    Pt operator+(Pt p) { return { x + p.x, y + p.y }; }
    Pt operator-(Pt p) { return { x - p.x, y - p.y }; }
    Pt operator*(T k) { return { x * k, y * k }; }
    Pt operator/(T k) { return { x / k, y / k }; }
    bool operator==(Pt p) { return x == p.x && y == p.y; }
    bool operator!=(Pt p) { return x != p.x || y != p.y; }
    friend istream &operator>>(istream &is, Pt &p) {
        return is >> p.x >> p.y;
    }
    friend ostream &operator<<(ostream &os, const Pt &p) {
        return os << "(" << p.x << ", " << p.y << ")";
    }
};
int sign(double x)
{ return fabs(x) <= eps ? 0 : (x > 0 ? 1 : -1); }
using P = Pt<ll>;
ll dot(P a, P b) { return a.x * b.x + a.y * b.y; }
ll cross(P a, P b) { return a.x * b.y - a.y * b.x; }
ll square(P p) { return dot(p, p); }
double abs(P p) { return sqrt(square(p)); }
int ori(P o, P a, P b) { return sign(cross(a - o, b - o)); }
P norm(P p) { return p / abs(p); }
P rot(P p) { return { -p.y, p.x }; }

struct Line { P a, b; };
double abs(Line l) { return abs(l.a - l.b); }
bool parallel(Line l1, Line l2)
{ return cross(l1.b - l1.a, l2.b - l2.a) == 0; }
double dist(P a, P b) { return abs(a - b); }
P lineIntersection(Line l1, Line l2) {
    return l1.a + (l1.b - l1.a) * (cross(l2.b - l2.a, l1.a - l2.a) / cross(l2.b - l2.a, l1.a - l1.b));
}
bool pointOnSegment(P p, Line l) {
    return cross(p - l.a, l.b - l.a) == 0 && min(l.a.x, l.b.x) <= p.x && p.x <= max(l.a.x, l.b.x)
        && min(l.a.y, l.b.y) <= p.y && p.y <= max(l.a.y, l.b.y);
}
// 0 : not intersect
// 1 : strictly intersect
// 2 : overlap
// 3 : intersect at endpoint
tuple<int, P, P> segmentIntersection(Line l1, Line l2) {
    if (max(l1.a.x, l1.b.x) < min(l2.a.x, l2.b.x) ||
        min(l1.a.x, l1.b.x) > max(l2.a.x, l2.b.x) ||
        max(l1.a.y, l1.b.y) < min(l2.a.y, l2.b.y) ||
        min(l1.a.y, l1.b.y) > max(l2.a.y, l2.b.y))
        return {0, {}, {}};
    if (cross(l1.b - l1.a, l2.b - l2.a) == 0) {
        if (cross(l1.b - l1.a, l2.a - l1.a) != 0) {
            return {0, {}, {}};
        } else {
            auto maxx1 = max(l1.a.x, l1.b.x);
            auto minx1 = min(l1.a.x, l1.b.x);
            auto maxy1 = max(l1.a.y, l1.b.y);
            auto miny1 = min(l1.a.y, l1.b.y);
            auto maxx2 = max(l2.a.x, l2.b.x);
            auto minx2 = min(l2.a.x, l2.b.x);
            auto maxy2 = max(l2.a.y, l2.b.y);
            auto miny2 = min(l2.a.y, l2.b.y);
            P p1(max(minx1, minx2), max(miny1, miny2));
            P p2(min(maxx1, maxx2), min(maxy1, maxy2));
            if (!pointOnSegment(p1, l1)) swap(p1.y, p2.y);
            if (p1 == p2) return {3, p1, p2};
            else return {2, p1, p2};
        }
    }
    auto cp1 = cross(l2.a - l1.a, l2.b - l1.a);
    auto cp2 = cross(l2.a - l1.b, l2.b - l1.b);
    auto cp3 = cross(l1.a - l2.a, l1.b - l2.a);
    auto cp4 = cross(l1.a - l2.b, l1.b - l2.b);
    if ((cp1 > 0 && cp2 > 0) || (cp1 < 0 && cp2 < 0) || (cp3 > 0 && cp4 > 0) || (cp3 < 0 && cp4 < 0)) return {0, P(), P()};
    P p = lineIntersection(l1, l2);
    if (cp1 != 0 && cp2 != 0 && cp3 != 0 && cp4 != 0) return {1, p, p};
    else return {3, p, p};
}

double distPL(P &p, Line &l)
{ return abs(cross(l.a - l.b, l.a - p)) / abs(l); }
double distancePS(P &p, Line &l) {
    if (dot(p - l.a, l.b - l.a) < 0) return dist(p, l.a);
    if (dot(p - l.b, l.a - l.b) < 0) return dist(p, l.b);
    return distPL(p, l);
}
double distanceSS(Line l1, Line l2) {
    if (get<0>(segmentIntersection(l1, l2)) != 0) return 0.0;
    return min({distancePS(l1.a, l2), distancePS(l1.b, l2), distancePS(l2.a, l1), distancePS(l2.b, l1)});
}

bool pointOnLineLeft(P p, Line l) {
    return cross(l.b - l.a, p - l.a) > 0;
}
bool pointInPolygon(P a, vector<P> p) {
    int n = p.size(), t = 0;
    for (int i = 0; i < n; i++)
        if (pointOnSegment(a, {p[i], p[(i + 1) % n]})) return true;
    for (int i = 0; i < n; i++) {
        P u = p[i], v = p[(i + 1) % n];
        if (u.x < a.x && v.x >= a.x && pointOnLineLeft(a, {v, u})) t ^= 1;
        if (u.x >= a.x && v.x < a.x && pointOnLineLeft(a, {u, v})) t ^= 1;
    }
    return t == 1;
}
// 0 : strictly outside
// 1 : on boundary
// 2 : strictly inside
int pointInConvexPolygon(P a, const vector<P> &p) {
    int n = p.size();
    if (n == 0) return 0;
    else if (n <= 2) return pointOnSegment(a, {p[0], p.back()});
    if (pointOnSegment(a, {p[0], p[1]}) || pointOnSegment(a, {p[0], p[n - 1]})) return 1;
    else if (pointOnLineLeft(a, {p[1], p[0]}) || pointOnLineLeft(a, {p[0], p[n - 1]})) return 0;
    int lo = 1, hi = n - 2;
    while (lo < hi) {
        int x = (lo + hi + 1) / 2;
        if (pointOnLineLeft(a, {p[0], p[x]})) lo = x;
        else hi = x - 1;
    }
    if (pointOnLineLeft(a, {p[lo], p[lo + 1]})) return 2;
    else return pointOnSegment(a, {p[lo], p[lo + 1]});
}
bool lineIntersectsPolygon(Line l, const vector<P> &p) {
    int n = p.size();
    P a = l.a, b = l.b;
    for (int i = 0; i < n; i++) {
        Line seg {p[i], p[(i + 1) % n]};
        if (cross(b - a, seg.a - a) == 0 || cross(b - a, seg.b - a) == 0) return true;
        if ((cross(b - a, seg.a - a) > 0) ^ (cross(b - a, seg.b - a) > 0)) return true;
    }
    return false;
}
bool segmentInPolygon(Line l, vector<P> p) {
    int n = p.size();
    if (!pointInPolygon(l.a, p)) return false;
    if (!pointInPolygon(l.b, p)) return false;
    for (int i = 0; i < n; i++) {
        auto u = p[i];
        auto v = p[(i + 1) % n];
        auto w = p[(i + 2) % n];
        auto [t, p1, p2] = segmentIntersection(l, {u, v});
        if (t == 1) return false;
        if (t == 0) continue;
        if (t == 2) {
            if (pointOnSegment(v, l) && v != l.a && v != l.b && cross(v - u, w - v) > 0) return false;
        } else {
            if (p1 != u && p1 != v) {
                if (pointOnLineLeft(l.a, {v, u}) || pointOnLineLeft(l.b, {v, u})) return false;
            } else if (p1 == v) {
                if (l.a == v) {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, l) && pointOnLineLeft(w, {u, v})) return false;
                    } else if (pointOnLineLeft(w, l) || pointOnLineLeft(w, {u, v})) return false;
                } else if (l.b == v) {
                    if (pointOnLineLeft(u, {l.b, l.a})) {
                        if (pointOnLineLeft(w, {l.b, l.a}) && pointOnLineLeft(w, {u, v})) return false;
                    } else if (pointOnLineLeft(w, {l.b, l.a}) || pointOnLineLeft(w, {u, v})) return false;
                } else {
                    if (pointOnLineLeft(u, l)) {
                        if (pointOnLineLeft(w, {l.b, l.a}) || pointOnLineLeft(w, {u, v})) return false;
                    } else if (pointOnLineLeft(w, l) || pointOnLineLeft(w, {u, v})) return false;
                }
            }
        }
    }
    return true;
}
vector<P> convexHull(vector<P> a) {
    sort(a.begin(), a.end(), [](const P &l, const P &r) {
        return l.x == r.x ? l.y < r.y : l.x < r.x;
    });
    a.resize(unique(a.begin(), a.end()) - a.begin());
    if (a.size() <= 1) return a;
    vector<P> h(a.size() + 1);
    int s = 0, t = 0;
    for (int i = 0; i < 2; i++, s = --t) {
        for (P p : a) {
            while (t >= s + 2 && cross(h[t - 1] - h[t - 2], p - h[t - 2]) <= 0) t--;
            h[t++] = p;
        }
        reverse(a.begin(), a.end());
    }
    return {h.begin(), h.begin() + t};
}

vector<P> hp(vector<Line> lines) {
    auto sgn = [](P p) { return p.y > 0 || (p.y == 0 && p.x > 0) ? 1 : -1; };
    sort(lines.begin(), lines.end(), [&](auto l1, auto l2) {
        auto d1 = l1.b - l1.a;
        auto d2 = l2.b - l2.a;
        if (sgn(d1) != sgn(d2))
            return sgn(d1) == 1;
        return cross(d1, d2) > 0;
    });
    deque<Line> ls;
    deque<P> ps;
    for (auto l : lines) {
        if (ls.empty()) {
            ls.push_back(l);
            continue;
        }
        while (!ps.empty() && !pointOnLineLeft(ps.back(), l)) ps.pop_back(), ls.pop_back();
        while (!ps.empty() && !pointOnLineLeft(ps[0], l)) ps.pop_front(), ls.pop_front();
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

void recursiveSol() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int n; cin >> n;
    const ll inf = 8E18;
    vector<P> a(n);
    for (int i = 0; i < n; i++) {
        ll x, y; cin >> x >> y;
        a[i] = P(x, y);
    }
    struct sortY { bool operator()(const P &a, const P &b) const { return a.y < b.y; } };
    struct sortXY {
        bool operator()(const P &a, const P &b) const {
            return a.x == b.x ? a.y < b.y : a.x < b.x;
        }
    };
    sort(a.begin(), a.end(), sortXY());
    vector<P> t(n);
    auto divide = [&](auto &&self, int l, int r) -> ll {
        if (l == r) return inf;
        int m = (l + r) / 2;	
        ll ans = min(self(self, l, m), self(self, m + 1, r));
        ll midval = a[m].x;
        ll p = 0;
        for (int i = l; i <= r; i++)
            if ((midval - a[i].x) * (midval - a[i].x) <= ans)
                t[p++] = a[i];
        sort(t.begin(), t.begin() + p, sortY());
        for (int i = 0; i < p; i++) {
            for (int j = i + 1; j < p; j++) {
                ans = min(ans, square(t[i] - t[j]));
                if ((t[i].y - t[j].y) * (t[i].y - t[j].y) > ans) break;
            } 
        }
        return ans;
    };
    cout << divide(divide, 0, n - 1) << "\n";
}

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info>
struct KDTree { // 1-indexed
    static constexpr int DIM = Info::DIM;
    int n, rt;
    vector<Info> info;
    vector<int> l, r;
    KDTree(int n, const vector<Info> &info) : n(n), info(info), l(n + 1), r(n + 1) {
        rt = rebuild(1, n);
    }
    void pull(int p) {
        info[p].L = info[p].R = info[p].x;
        info[p].pull(info[l[p]], info[r[p]]);
        for (int ch : {l[p], r[p]}) {
            if (!ch) continue;
            for (int k = 0; k < DIM; k++) {
                info[p].L[k] = min(info[p].L[k], info[ch].L[k]);
                info[p].R[k] = max(info[p].R[k], info[ch].R[k]);
            }
        }
    }
    int rebuild(int l, int r, int dep = 0) {
        if (r == l) return 0;
        int m = (l + r) / 2;
        double avx = 0, avy = 0, vax = 0, vay = 0;  // average variance
        for (int i = l; i < r; i++) {
            avx += info[i].x[0];
            avy += info[i].x[1];
        }
        avx /= (double)(r - l);
        avy /= (double)(r - l);
        for (int i = l; i < r; i++) {
            vax += (info[i].x[0] - avx) * (info[i].x[0] - avx);
            vay += (info[i].x[1] - avy) * (info[i].x[1] - avy);
        }
        if (vax >= vay) {
            nth_element(info.begin() + l, info.begin() + m, info.begin() + r,
                [&](const Info &x, const Info &y) { return x.x[0] < y.x[0]; });
        } else {
            nth_element(info.begin() + l, info.begin() + m, info.begin() + r,
                [&](const Info &x, const Info &y) { return x.x[1] < y.x[1]; });
        }
        this->l[m] = rebuild(l, m, (dep + 1) % DIM);
        this->r[m] = rebuild(m + 1, r, (dep + 1) % DIM);
        pull(m);
        return m;
    }
    ll ans = 9E18;
    ll dist(int a, int b) {
        return (info[a].x[0] - info[b].x[0]) * (info[a].x[0] - info[b].x[0]) + 
        (info[a].x[1] - info[b].x[1]) * (info[a].x[1] - info[b].x[1]);
    }
    void query(int p, int x) {
        if (!p) return;
        if (p != x) ans = min(ans, dist(x, p));
        ll distl = info[x].f(info[l[p]]);
        ll distr = info[x].f(info[r[p]]);
        if (distl < ans && distr < ans) {
            if (distl < distr) {
                query(l[p], x);
                if (distr < ans) {
                    query(r[p], x);
                }
            } else {
                query(r[p], x);
                if (distl < ans) {
                    query(l[p], x);
                }
            }
        } else {
            if (distl < ans) query(l[p], x);
            if (distr < ans) query(r[p], x);
        }
    }
};
struct Info {
    static constexpr int DIM = 2;
    array<ll, DIM> x, L, R;
    ll distl, distr;
    ll f(const Info &i) {
        ll ret = 0;
        if (i.L[0] > x[0]) ret += (i.L[0] - x[0]) * (i.L[0] - x[0]);
        if (i.R[0] < x[0]) ret += (x[0] - i.R[0]) * (x[0] - i.R[0]);
        if (i.L[1] > x[1]) ret += (i.L[1] - x[1]) * (i.L[1] - x[1]);
        if (i.R[1] < x[1]) ret += (x[1] - i.R[1]) * (x[1] - i.R[1]);
        return ret;
    }
    void pull(const Info &l, const Info &r) {
        distl = f(l);
        distr = f(r);
    }
};

void ktSol() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<Info> info(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> info[i].x[0] >> info[i].x[1];
    }
    KDTree<Info> kt(n, info);
    for (int i = 1; i <= n; i++) {
        kt.query(kt.rt, i);
    }
    cout << kt.ans << "\n";
}

int main() {
    // recursiveSol()
    auto s = chrono::high_resolution_clock::now();
    recursiveSol();
    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}