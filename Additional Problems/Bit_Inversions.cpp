#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <class Info>
struct Seg {    // 左閉右開寫法
    int n;
    vector<Info> info;
    Seg() : n(0) {}
    Seg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template <class T>
    Seg(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
            // cerr << "Merge:\n";
            // cerr << "l = " << l << ", r = " << m - 1 << ", " << info[2 * p] << "\n";
            // cerr << "l = " << m << ", r = " << r - 1 << ", " << info[2 * p + 1] << "\n";
            // cerr << "Merge to:\n";
            // cerr << "l = " << l << ", r = " << r - 1 << ", " << info[p] << "\n\n";
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
        // cerr << "Merge:\n";
        // cerr << "l = " << l << ", r = " << m - 1 << ", " << info[2 * p] << "\n";
        // cerr << "l = " << m << ", r = " << r - 1 << ", " << info[2 * p + 1] << "\n";
        // cerr << "Merge to:\n";
        // cerr << "l = " << l << ", r = " << r - 1 << ", " << info[p] << "\n\n";
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
// ---define structure and info plus---
struct Info {
    int n = 1;
    int pref_one = 0;
    int suff_one = 0;
    int pref_zero = 0;
    int suff_zero = 0;
    int max = 0;
    friend ostream& operator<<(ostream& os, const Info &a) {
        return os << "pref one = " << a.pref_one << ", pref zero = " << a.pref_zero << ", suff one = " << a.suff_one << ", suff zero = " << a.suff_zero << ", max = " << a.max;
    }
};
Info operator+(const Info &a, const Info &b) {
    Info i;
    i.n = a.n + b.n;

    i.pref_one = a.pref_one;
    if (a.pref_one == a.n) i.pref_one += b.pref_one;
    i.suff_one = b.suff_one;
    if (b.pref_one == b.n) i.suff_one += a.suff_one;

    i.pref_zero = a.pref_zero;
    if (a.pref_zero == a.n) i.pref_zero += b.pref_zero;
    i.suff_zero = b.suff_zero;
    if (b.pref_zero == b.n) i.suff_zero += a.suff_zero;

    i.max = max(a.max, b.max);
    i.max = max({i.max, a.suff_one + b.pref_one, a.suff_zero + b.pref_zero}); // 中間組合

    return i;
}

void solve() {
    string s;
    cin >> s;
    int n = s.size();
    // cerr << n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = s[i] - '0';
    }

    int q;
    cin >> q;
    vector<Info> init(n);
    for (int i = 0; i < n; i++) {
        if (a[i]) {
            init[i].pref_one = init[i].suff_one = 1;
        } else {
            init[i].pref_zero = init[i].suff_zero = 1;
        }
        init[i].max = 1;
    }

    Seg<Info> seg(init);
    for (int i = 0; i < q; i++) {
        int p;
        cin >> p;
        p--;
        a[p] ^= 1;
        Info new_info;
        if (a[p]) {
            new_info.pref_one = new_info.suff_one = 1;
        } else {
            new_info.pref_zero = new_info.suff_zero = 1;
        }
        // for (int x : a) cerr << x;
        // cerr << "\n";
        seg.modify(p, new_info);
        cout << seg.query(0, n).max << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("1.in", "r", stdin);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}