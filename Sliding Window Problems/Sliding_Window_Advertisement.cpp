#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 應用: dp(i) = h(i) + min/max(A(j)X(i) + B(j)), for j ≤ r(i)
//        y    =  c   +          m  x   +   b
constexpr ll inf = 4E18;
struct Line {
    ll m, b;
    Line(ll m = 0, ll b = -inf) : m(m), b(b) {}
    ll eval(ll x) { return m * x + b; }
};
struct LiChaoSeg { // 取 max 再變換就好
    int n; vector<Line> info;
    LiChaoSeg(int n) : n(n), info(4 << __lg(n), Line()) {}
    void addLine(Line line) { update(line, 1, 0, n); }
    void rangeAddLine(Line line, int ql, int qr) { rangeUpdate(line, 1, 0, n, ql, qr); }
    ll query(int x) { return query(x, 1, 0, n); }
private:
    void update(Line line, int p, int l, int r) {
        int m = (l + r) / 2;
        bool left = line.eval(l) > info[p].eval(l);
        bool mid = line.eval(m) > info[p].eval(m);
        if (mid) swap(info[p], line); // 如果新線段比較好
        if (r - l == 1) return;
        else if (left != mid) update(line, 2 * p, l, m); // 代表左半有交點
        else update(line, 2 * p + 1, m, r); // 代表如果有交點一定在右半
    }
    void rangeUpdate(Line line, int p, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) return;
        if (l >= ql && r <= qr) return update(line, p, l, r);
        int m = (l + r) / 2;
        rangeUpdate(line, 2 * p, l, m, ql, qr);
        rangeUpdate(line, 2 * p + 1, m, r, ql, qr);
    }
    ll query(int x, int p, int l, int r) {
        if (r - l == 1) return info[p].eval(x);
        int m = (l + r) / 2;
        if (x < m) return max(info[p].eval(x), query(x, 2 * p, l, m));
        else return max(info[p].eval(x), query(x, 2 * p + 1, m, r));
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
    // ios::sync_with_stdio(false);
    // cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    RMQ<int> rmq(a);
    LiChaoSeg seg(n);
    // deque<pair<int, int>> dq;
    // for (int i = 0; i < n; i++) {
    //     int l = i;
    //     while (!dq.empty() && dq.back().second >= a[i]) {
    //         auto [L, H] = dq.back();
    //         l = L;
    //         dq.pop_back();
    //     }
    //     l = max(l, i - k + 1);
    //     // if (!dq.empty()) {
    //     //     int l = max(dq.back().first, i - k + 1);
    //     //     seg.rangeAddLine({dq.back().second, -1LL * (l - 1) * dq.back().second}, l, i + 1);
    //     //     // cerr << "i = " << i << ", m = " << dq.back().second << ", c = " << -1LL * (l - 1) * dq.back().second << ", l = " << l << "\n";
    //     // }
    //     dq.emplace_back(l, a[i]);
    //     seg.rangeAddLine({a[i], -1LL * (l - 1) * a[i]}, l, i + 1);
    //     int lo = i, hi = n - 1;
    //     while (lo < hi) {
    //         int m = (lo + hi + 1) / 2;
    //         if (a[m] >= a[i]) {
    //             lo = m;
    //         } else {
    //             hi = m - 1;
    //         }
    //     }
    //     seg.rangeAddLine({0, 1LL * (i - l + 1) * a[i]}, i, l + k);
    //     // seg.rangeAddLine({-a[i], 1LL * (i - l + 1) * a[i] + 1LL * a[i] * (l + k - 1)}, l + k - 1, n);
    //     seg.rangeAddLine({-a[i], 1LL * (i + k) * a[i]}, l + k - 1, n);
    //     cerr << "i = " << i << ", m = " << a[i] << ", c = " << -1LL * (l - 1) * a[i] << ", l = " << l << "\n";
    //     if (i >= k - 1) {
    //         cout << seg.query(i) << " \n"[i == n - 1];
    //     }
    // }

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