// 掃描線
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info, class Tag = bool()>
struct SegmentTree { // [l, r), uncomment /**/ to lazy
    int n;
    vector<Info> info;
    vector<Tag> tag;
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
        tag.assign(4 << __lg(n), Tag());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[p * 2] + info[p * 2 + 1];
    }
    void apply(int p, int l, int r, const Tag &v) {
        info[p].apply(l, r, v);
        tag[p].apply(v);
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
        return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }
    void rangeApply(int p, int l, int r, int ql, int qr, const Tag &v) {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        rangeApply(p * 2, l, m, ql, qr, v);
        rangeApply(p * 2 + 1, m, r, ql, qr, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n, l, r, v);
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

vector<ll> idToVal;
struct Tag {
    int add = 0;
    void apply(const Tag& v) {
        add += v.add;
    }
};
struct Info {
    ll val = 0;
    int cnt = 0;
    ll subsum = 0;
    void apply(int l, int r, const Tag &v) & {
        cnt += v.add;
        if (cnt) {
            val = idToVal[r] - idToVal[l];
        } else {
            val = subsum;
        }
    }
    Info &operator=(const Info &rhs) & {
        subsum = rhs.val;
        if (cnt == 0) {
            val = subsum;
        }
        return *this;
    }
};
Info operator+(const Info &a, const Info &b) {
    return { a.val + b.val, 0, a.val + b.val };
}

struct Line {
    ll x, yl, yr;
    bool add;
    const bool operator<(const Line &rhs) {
        return x < rhs.x;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<Line> eve;
    int n; cin >> n;
    vector<ll> ys;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        eve.push_back({x1, y1, y2, true});
        eve.push_back({x2, y1, y2, false});
        ys.push_back(y1);
        ys.push_back(y2);
    }
    sort(ys.begin(), ys.end());
    ys.erase(unique(ys.begin(), ys.end()), ys.end());
    for (int x : ys) {
        idToVal.push_back(x);
    }
    sort(eve.begin(), eve.end());

    int sz = idToVal.size();

    SegmentTree<Info, Tag> seg(sz);
    
    ll last_x = eve[0].x;
    ll ans = 0;

    for (const auto &e : eve) {
        ll width = e.x - last_x;
        ans += width * seg.query(0, sz).val;
        int l = lower_bound(idToVal.begin(), idToVal.end(), e.yl) - idToVal.begin();
        int r = lower_bound(idToVal.begin(), idToVal.end(), e.yr) - idToVal.begin();
        seg.rangeApply(l, r, { e.add ? 1 : -1 });
        last_x = e.x;
    }
    
    cout << ans << "\n";
    return 0;
}