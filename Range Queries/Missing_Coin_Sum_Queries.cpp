#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

void solve_bin() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<vector<int>> grp(30);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        for (int j = 0; j < 30; j++) {
            if (a[i] < (1 << (j + 1))) {
                grp[j].push_back(i);
                break;
            }
        }
    }
    vector<RMQ<int>> rmq(30);
    vector<vector<ll>> pref(30, vector<ll>(1));
    for (int i = 0; i < 30; i++) {
        vector<int> tmp;
        for (auto j : grp[i]) {
            tmp.push_back(a[j]);
            pref[i].push_back(pref[i].back() + a[j]);
        }
        if (!tmp.empty()) {
            rmq[i].init(tmp);
        }
    }

    vector<pair<int, int>> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].first >> qry[i].second;
        --qry[i].first;
    }

    for (int i = 0; i < q; i++) {
        auto [l, r] = qry[i];
        ll ans = 0;
        for (int j = 0; j < 30; j++) {
            int nl = lower_bound(grp[j].begin(), grp[j].end(), l) - grp[j].begin();
            int nr = lower_bound(grp[j].begin(), grp[j].end(), r) - grp[j].begin();
            if (nl == nr) continue;
            int mn = rmq[j](nl, nr);
            if (ans + 1 >= mn) {
                ans += pref[j][nr] - pref[j][nl];
            } else {
                break;
            }
        }
        cout << ans + 1 << "\n";
    }
}

template<class Info> struct PST {
    struct Node {
        Info info = Info();
        int lc = 0, rc = 0;
    };
    int n;
    vector<Node> nd;
    vector<int> rt;
    PST(int n) : n(n), nd(1), rt(1, 0) {}
    template<class T> PST(const vector<T> &v) {
        n = v.size();
        nd.assign(1, Node());
        rt.clear();
        function<int(int, int)> build = [&](int l, int r) {
            int id = nd.size();
            nd.emplace_back();
            if (r - l == 1) {
                nd[id].info = v[l];
                return id;
            }
            int m = (l + r) / 2;
            int lc = build(l, m);
            int rc = build(m, r);
            nd[id].lc = lc;
            nd[id].rc = rc;
            pull(nd[id]);
            return id;
        };
        rt.push_back(build(0, n));
    }
    void pull(Node &p) { p.info = nd[p.lc].info + nd[p.rc].info; }
    int copy(int p) { // copy 一個 node
        nd.push_back(nd[p]);
        return nd.size() - 1;
    }
    int generate() { // 創立新的 node
        nd.emplace_back();
        return nd.size() - 1;
    }
    void modify(int x, const Info &i, int ver = 0) {
        if (int(rt.size()) <= ver) rt.resize(ver + 1);
        rt[ver] = modify(x, i, 0, n, rt[ver]);
    }
    int modify(int x, const Info &i, int l, int r, int p) {
        p = p ? copy(p) : generate();
        if (r - l == 1) {
            nd[p].info = nd[p].info + i;
            return p;
        }
        int m = (l + r) / 2;
        if (x < m) {
            int y = modify(x, i, l, m, nd[p].lc);
            nd[p].lc = y;
        } else {
            int y = modify(x, i, m, r, nd[p].rc);
            nd[p].rc = y;
        }
        pull(nd[p]);
        return p;
    }
    Info query(int ql, int qr, int ver = 0)
    { return query(ql, qr, 0, n, rt[ver]); }
    Info query(int ql, int qr, int l, int r, int p) {
        if (l >= qr || r <= ql || p == 0) return Info();
        if (ql <= l && r <= qr) return nd[p].info;
        int m = (l + r) / 2;
        return query(ql, qr, l, m, nd[p].lc) + query(ql, qr, m, r, nd[p].rc);
    }
    void createVersion(int ver) { rt.push_back(rt[ver]); }
    void resize(int n) { rt.resize(n); }
};
struct Info {
    ll sum = 0;
};
Info operator+(const Info &a, const Info &b) {
    Info res;
    res.sum = a.sum + b.sum;
    return res;
}

void solve_PST() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), val;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        val.push_back(a[i]);
    }
    sort(val.begin(), val.end());
    val.resize(unique(val.begin(), val.end()) - val.begin());
    PST<Info> pst(val.size());
    for (int i = 0; i < n; i++) {
        pst.createVersion(i);
        int p = lower_bound(val.begin(), val.end(), a[i]) - val.begin();
        pst.modify(p, {a[i]}, i + 1);
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        ll ans = 0;
        while (true) {
            int p = upper_bound(val.begin(), val.end(), ans + 1) - val.begin();
            ll nxt = pst.query(0, p, r + 1).sum - pst.query(0, p, l).sum;
            if (nxt > ans) {
                ans = nxt;
            } else {
                break;
            }
        }
        cout << ans + 1 << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_bin();
    solve_PST();
    return 0;
}