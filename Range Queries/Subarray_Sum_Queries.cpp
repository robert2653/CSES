#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info, class Tag = bool()>
struct SegmentTree { // [l, r), uncomment /**/ to lazy
    int n;
    vector<Info> info;
    SegmentTree() : n(0) {}
    SegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }

    template<class T>
    SegmentTree(vector<T> init_) {
        init(init_);
    }

    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }

    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
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
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
        return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) return -1;
        if (l >= x && r <= y && !pred(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1)
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};

struct Info {
    ll pref = 0;
    ll sum = 0;
    ll suff = 0;
    ll mx = 0;
    Info &operator=(const int &rhs) & {
        pref = sum = suff = mx = rhs;
        return *this;
    }
};
Info operator+(const Info &a, const Info &b) {
    Info c;
    c.sum = a.sum + b.sum;
    c.pref = max(a.sum + b.pref, a.pref);
    c.suff = max(a.suff + b.sum, b.suff);
    c.mx = max({a.mx, b.mx, a.suff + b.pref});
    return c;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegmentTree<Info> seg(a);
    
    while (q--) {
        int p, x;
        cin >> p >> x;
        Info i;
        i = x;
        seg.modify(p - 1, i);
        cout << max(0LL, seg.query(0, n).mx) << "\n";
    }
    return 0;
}