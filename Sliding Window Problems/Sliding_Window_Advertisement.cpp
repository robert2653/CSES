#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 應用: dp(i) = h(i) + min/max(A(j)X(i) + B(j)), for j ≤ r(i)
//        y    =  c   +          m  x   +   b
template<class T, class F = less<ll>>
struct LiChaoSeg {
    F cmp = F();
    static const T inf = max(numeric_limits<T>::lowest() / 2, numeric_limits<T>::max() / 2, F());
    struct Line {
        T m, b;
        Line(T m = 0, T b = inf) : m(m), b(b) {}
        T eval(T x) const { return m * x + b; }
    };
    struct Node {
        Line line;
        ll l = -1, r = -1;
    };
    ll n;
    vector<Node> nd;
    LiChaoSeg(ll n) : n(n) { newNode(); }
    void addLine(Line line) { update(0, 0, n, line); }
    void rangeAddLine(Line line, ll ql, ll qr) { rangeUpdate(0, 0, n, ql, qr, line); }
    T query(ll x) { return query(x, 0, 0, n); }
private:
    int newNode() {
        nd.emplace_back();
        return nd.size() - 1;
    }
    void update(int p, ll l, ll r, Line line) {
        ll m = (l + r) / 2;
        bool left = cmp(line.eval(l), nd[p].line.eval(l));
        bool mid = cmp(line.eval(m), nd[p].line.eval(m));
        if (mid) swap(nd[p].line, line);
        if (r - l == 1) return;
        if (left != mid) {
            if (nd[p].l == -1) nd[p].l = newNode();
            update(nd[p].l, l, m, line);
        } else {
            if (nd[p].r == -1) nd[p].r = newNode();
            update(nd[p].r, m, r, line);
        }
    }
    void rangeUpdate(int p, ll l, ll r, ll ql, ll qr, Line line) {
        if (r <= ql || l >= qr) return;
        if (ql <= l && r <= qr) return update(p, l, r, line);
        if (nd[p].l == -1) nd[p].l = newNode();
        if (nd[p].r == -1) nd[p].r = newNode();
        ll m = (l + r) / 2;
        rangeUpdate(nd[p].l, l, m, ql, qr, line);
        rangeUpdate(nd[p].r, m, r, ql, qr, line);
    }
    T query(ll x, int p, ll l, ll r) {
        if (p == -1) return inf;
        ll m = (l + r) / 2;
        if (x < m) return min(nd[p].line.eval(x), query(x, nd[p].l, l, m), cmp);
        else return min(nd[p].line.eval(x), query(x, nd[p].r, m, r), cmp);
    }
};
template<class T, class F = less<T>>
struct RMQ { // [l, r)
    int n;
    F cmp = F();
    vector<vector<T>> g;
    RMQ() {}
    RMQ(const vector<T> &a, F cmp = F()) : cmp(cmp) {
        init(a);
    }
    void init(const vector<T> &a) {
        n = a.size();
        int lg = __lg(n);
        g.resize(lg + 1);
        g[0] = a;
        for (int j = 1; j <= lg; j++) {
            g[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++)
                g[j][i] = min(g[j - 1][i], g[j - 1][i + (1 << (j - 1))], cmp);
        }
    }
    T operator()(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int lg = __lg(r - l);
        return min(g[lg][l], g[lg][r - (1 << lg)], cmp);
    }
};
// ans[i] = max((i - stk[j].first + 1) * stk[j].second)
// = max(i * stk[j].second - (stk[j].first - 1) * stk[j].second)
//       x *    m          -                    c
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    RMQ<int> rmq(a);
    LiChaoSeg<ll, greater<>> seg(n);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        // >= x 的左界跟右界
        int l = -1, r = -1;
        int lo = 0, hi = i;
        while (lo < hi) {
            int m = (lo + hi) / 2;
            if (rmq(m, i + 1) >= x) {
                hi = m;
            } else {
                lo = m + 1;
            }
        }
        l = lo;

        lo = i, hi = n - 1;
        while (lo < hi) {
            int m = (lo + hi + 1) / 2;
            if (rmq(i, m + 1) >= x) {
                lo = m;
            } else {
                hi = m - 1;
            }
        }
        r = lo;
        
        ll peak = 1LL * a[i] * min(r - l + 1, k);
        seg.rangeAddLine({a[i], -1LL * (l - 1) * a[i]}, l, min(l + k, r + 1));
        seg.rangeAddLine({0, peak}, min(l + k, r + 1) - 1, max(l + k, r + 1));
        seg.rangeAddLine({-a[i], peak + 1LL * a[i] * (max(l + k, r + 1) - 1)}, max(l + k, r + 1) - 1, n);
        // cerr << l << " " << r << " " << peak << "\n";
    }
    for (int i = k - 1; i < n; i++) {
        cout << seg.query(i) << " \n"[i == n - 1];
    }
    return 0;
}