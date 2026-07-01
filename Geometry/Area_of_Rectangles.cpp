// 掃描線
#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info, class Tag> struct LazySegmentTreeDynamic {
    struct Node {
        Info info = Info();
        Tag tag = Tag();
        bool isLazy = false;
        int lc = 0, rc = 0;
    };
    int n, rt;
    vector<Node> nd;
    LazySegmentTreeDynamic(int n) : n(n), rt(0), nd(1) {}
    int generate() {
        nd.emplace_back();
        return nd.size() - 1;
    }
    void pull(int p) { nd[p].info = nd[nd[p].lc].info + nd[nd[p].rc].info; }
    Info query(int ql, int qr) { return query(ql, qr, 0, n, rt); }
    Info query(int ql, int qr, int l, int r, int p) {
        if (l >= qr || r <= ql || p == 0) return Info();
        if (ql <= l && r <= qr) return nd[p].info;
        push(l, r, p);
        int m = (l + r) / 2;
        return query(ql, qr, l, m, nd[p].lc) + query(ql, qr, m, r, nd[p].rc);
    }
    void apply(const Tag &t, int l, int r, int p) {
        nd[p].info.apply(t, l, r);
        nd[p].tag.apply(t);
        nd[p].isLazy = true;
    }
    void push(int l, int r, int p) {
        if (!nd[p].isLazy) return;
        int m = (l + r) / 2;
        if (nd[p].lc == 0) nd[p].lc = generate();
        if (nd[p].rc == 0) nd[p].rc = generate();
        apply(nd[p].tag, l, m, nd[p].lc);
        apply(nd[p].tag, m, r, nd[p].rc);
        nd[p].tag = Tag();
        nd[p].isLazy = false;
    }
    void rangeApply(int ql, int qr, const Tag &t) { rt = rangeApply(ql, qr, t, 0, n, rt); }
    int rangeApply(int ql, int qr, const Tag &t, int l, int r, int p) {
        if (l >= qr || r <= ql) return p;
        if (p == 0) p = generate();
        if (ql <= l && r <= qr) {
            apply(t, l, r, p);
            return p;
        }
        // push(l, r, p);
        int m = (l + r) / 2;
        nd[p].lc = rangeApply(ql, qr, t, l, m, nd[p].lc);
        nd[p].rc = rangeApply(ql, qr, t, m, r, nd[p].rc);
        pull(p);
        return p;
    }
};

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
    void apply(const Tag &v, int l, int r) & {
        cnt += v.add;
        if (cnt) {
            val = r - l;
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
    const int sz = 1E9;
    for (int i = 0; i < n; i++) {
        ll x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if (x1 > x2) {
            swap(x1, x2);
        }
        if (y1 > y2) {
            swap(y1, y2);
        }
        y1 += sz / 2;
        y2 += sz / 2;
        eve.push_back({x1, y1, y2, true});
        eve.push_back({x2, y1, y2, false});
    }
    sort(eve.begin(), eve.end());

    LazySegmentTreeDynamic<Info, Tag> seg(sz);
    
    ll last_x = eve[0].x;
    ll ans = 0;

    for (const auto &e : eve) {
        ll width = e.x - last_x;
        ans += width * seg.query(0, sz).val;
        int l = e.yl;
        int r = e.yr;
        seg.rangeApply(l, r, { e.add ? 1 : -1 });
        last_x = e.x;
    }
    
    cout << ans << "\n";
    return 0;
}