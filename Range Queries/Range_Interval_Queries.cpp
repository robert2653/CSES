#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

template<class Info> struct PST {
    struct Node {
        Info info = Info();
        int lc = 0, rc = 0;
    };
    int n;
    vector<Node> nd;
    vector<int> rt;
    PST(int n) : n(n), nd(1), rt(1) {}
    void pull(Node &p) { p.info = nd[p.lc].info + nd[p.rc].info; }
    int copy(int p) { // copy 一個 node
        nd.push_back(nd[p]);
        return nd.size() - 1;
    }
    int generate() { // 創立新的 node
        nd.emplace_back();
        return nd.size() - 1;
    }
    void add(int x, const Info &i, int ver = 0) {
        if (int(rt.size()) <= ver) rt.resize(ver + 1);
        rt[ver] = add(x, i, 0, n, rt[ver]);
    }
    int add(int x, const Info &i, int l, int r, int p) {
        p = p ? copy(p) : generate();
        if (r - l == 1) {
            nd[p].info = nd[p].info + i;
            return p;
        }
        int m = (l + r) / 2;
        if (x < m) {
            nd[p].lc = add(x, i, l, m, nd[p].lc);
        } else {
            nd[p].rc = add(x, i, m, r, nd[p].rc);
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
    Info query2(int ql, int qr, int ver1, int ver2)
    { return query2(ql, qr, 0, n, rt[ver1], rt[ver2]); }
    Info query2(int ql, int qr, int l, int r, int p1, int p2) {
        if (l >= qr || r <= ql) return Info();
        if (ql <= l && r <= qr) return nd[p2].info - nd[p1].info;
        int m = (l + r) / 2;
        return query2(ql, qr, l, m, nd[p1].lc, nd[p2].lc)
             + query2(ql, qr, m, r, nd[p1].rc, nd[p2].rc);
    }
    void createVersion(int ver) { rt.push_back(rt[ver]); }
    void reserve(int q) {
        nd.reserve(q * (2 * __lg(n) + 2));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto s = a;
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());
    PST<int> pst(s.size());
    pst.reserve(q);
    for (int i = 0; i < n; i++) {
        pst.createVersion(i);
        int x = lower_bound(s.begin(), s.end(), a[i]) - s.begin();
        pst.add(x, 1, i + 1);
    }

    while (q--) {
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        a = lower_bound(s.begin(), s.end(), a) - s.begin();
        b = upper_bound(s.begin(), s.end(), b) - s.begin();
        int ans = pst.query2(a, b, l - 1, r);
        cout << ans << "\n";
    }
    
    return 0;
}