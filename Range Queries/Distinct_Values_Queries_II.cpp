#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

template<class Info> struct SegmentTree {
    int n;
    vector<Info> info;
    SegmentTree(int n) : n(n), info(4 << __lg(n)) {}
    SegmentTree(const vector<Info> &v) : n(v.size()), info(4 << __lg(n)) {
        auto build = [&](auto &&self, int l, int r, int p) {
            if (r - l == 1) {
                info[p] = v[l];
                return;
            }
            int m = (l + r) / 2;
            self(self, l, m, 2 * p);
            self(self, m, r, 2 * p + 1);
            pull(p);
        };
        build(build, 0, n, 1);
    }
    void pull(int p) { info[p] = info[2 * p] + info[2 * p + 1]; }
    void modify(int x, const Info &i) { modify(x, i, 0, n, 1); }
    void modify(int x, const Info &i, int l, int r, int p) {
        if (r - l == 1) {
            info[p] = i;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) modify(x, i, l, m, 2 * p);
        else modify(x, i, m, r, 2 * p + 1);
        pull(p);
    }
    Info query(int ql, int qr) { return query(ql, qr, 0, n, 1); } 
    Info query(int ql, int qr, int l, int r, int p) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
        return query(ql, qr, l, m, 2 * p) + query(ql, qr, m, r, 2 * p + 1);
    }
    template<class F> int findFirst(int ql, int qr, F &&f) {
        return findFirst(ql, qr, f, 0, n, 1);
    } // 若要找 last，先右子樹遞迴即可
    template<class F> int findFirst(int ql, int qr, F &&f, int l, int r, int p) {
        if (qr <= l || ql >= r) return -1;
        if (ql <= l && r <= qr && !f(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        int res = findFirst(ql, qr, f, l, m, 2 * p);
        if (res == -1) res = findFirst(ql, qr, f, m, r, 2 * p + 1);
        return res;
    }
};
struct Info {
    int mx = -1;
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mx = max(a.mx, b.mx);
    return c;
}
// 確保區間 [l, r] 內每個節點的值上次出現的位置都小於 l

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto s = a;

    vector<array<int, 3>> qry(q);
    for (int i = 0; i < q; i++) {
        int i1, i2, i3;
        cin >> i1 >> i2 >> i3;
        qry[i] = {i1, i2, i3};
        if (i1 == 1) s.push_back(i3);
    }
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    int m = s.size();
    for (auto &x : a) x = lower_bound(s.begin(), s.end(), x) - s.begin();
    for (auto &[i1, i2, i3] : qry) {
        if (i1 == 1) i3 = lower_bound(s.begin(), s.end(), i3) - s.begin();
    }

    vector<set<int>> pos(m);
    for (int i = 0; i < m; i++) {
        pos[i].insert(-1);
    }

    SegmentTree<Info> seg(n);
    for (int i = 0; i < n; i++) {
        int x = a[i];
        seg.modify(i, {*pos[x].rbegin()});
        pos[x].insert(i);
    }
    for (int i = 0; i < q; i++) {
        int op = qry[i][0];
        if (op == 1) {
            int p = qry[i][1] - 1;
            int x = qry[i][2];
            if (a[p] == x) continue;

            int old = a[p];
            auto pre = prev(pos[old].find(p));
            auto nxt = next(pos[old].find(p));
            if (nxt != pos[old].end()) {
                seg.modify(*nxt, {*pre});
            }

            pos[old].erase(p);
            a[p] = x;
            
            auto cur = pos[x].insert(p).first;
            pre = prev(cur);
            nxt = next(cur);
            seg.modify(p, {*pre});
            if (nxt != pos[x].end()) {
                seg.modify(*nxt, {*cur});
            }
        } else {
            int l = qry[i][1] - 1;
            int r = qry[i][2] - 1;
            int mx = seg.query(l, r + 1).mx;
            cout << (mx < l ? "YES" : "NO") << "\n";
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto s = chrono::high_resolution_clock::now();

    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    
    return 0;
}