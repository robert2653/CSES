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
const int inf = 2E9;
struct Info {
    array<int, 2> mn = {inf, inf};
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.mn[0] = min(a.mn[0], b.mn[0]);
    c.mn[1] = min(a.mn[1], b.mn[1]);
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a[i].mn[0] = x - i;
        a[i].mn[1] = x + i;
    }
    SegmentTree<Info> seg(a);
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int k, x;
            cin >> k >> x;
            k--;
            seg.modify(k, {x - k, x + k});
        } else {
            int k;
            cin >> k;
            k--;
            cout << min(seg.query(0, k + 1).mn[0] + k, seg.query(k, n).mn[1] - k) << "\n";
        }
    }
    
    return 0;
}