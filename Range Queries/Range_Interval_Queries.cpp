#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info>
struct PST {
    struct Node {
        Info info = Info();
        int lc = 0, rc = 0;
    };
    int n = 0;
    vector<Node> nd;
    vector<int> rt;
    PST() : n(0) {}
    PST(int n_, Info v_ = Info()) {
        init(n_, v_);
    }

    template<class T>
    PST(vector<T> init_) {
        init(init_);
    }

    void init(int n_, Info v_ = Info()) {
        init(vector<Info>(n_, v_));
    }
    
    template<class T>
    void init(vector<T> init_) {
        n = init_.size();
        nd.assign(1, Node());
        rt.clear();
        function<int(int, int)> build = [&](int l, int r) {
            int id = nd.size();
            nd.emplace_back();
            if (r - l == 1) {
                nd[id].info = init_[l];
                return id;
            }
            int m = (l + r) >> 1;
            nd[id].lc = build(l, m);
            nd[id].rc = build(m, r);
            pull(nd[id]);
            return id;
        };
        rt.push_back(build(0, n));
    }
    void pull(Node &t) {
        t.info = nd[t.lc].info + nd[t.rc].info;
    }
    int copy(int t) { // copy 一個 node
        nd.push_back(nd[t]);
        return nd.size() - 1;
    }
    int generate() { // 創立新的 node
        nd.emplace_back();
        return nd.size() - 1;
    }
    int modify(int t, int l, int r, int x, const Info &v) {
        t = t ? copy(t) : generate();
        if (r - l == 1) {
            nd[t].info = v;
            return t;
        }
        int m = (l + r) / 2;
        if (x < m) {
            nd[t].lc = modify(nd[t].lc, l, m, x, v);
        } else {
            nd[t].rc = modify(nd[t].rc, m, r, x, v);
        }
        pull(nd[t]);
        return t;
    }
    void modify(int ver, int p, const Info &i) {
        if (int(rt.size()) <= ver) rt.resize(ver + 1);
        rt[ver] = modify(rt[ver], 0, n, p, i);
    }
    Info query(int t, int l, int r, int ql, int qr) {
        if (l >= qr || r <= ql) return Info();
        if (ql <= l && r <= qr) return nd[t].info;
        int m = (l + r) / 2;
        return query(nd[t].lc, l, m, ql, qr) + query(nd[t].rc, m, r, ql, qr);
    }
    Info query(int ver, int ql, int qr) {
        return query(rt[ver], 0, n, ql, qr);
    }
    void createVersion(int ori_ver) {
        rt.push_back(copy(rt[ori_ver]));
    }
    void reserve(int n, int q) {
        nd.reserve(n + q * (2 * __lg(n) + 1));
        rt.reserve(q + 1);
    }
    void resize(int n) { rt.resize(n); }
};

template<class T>
struct StaticKth : PST<int> {
    int dct(T x) {
        return lower_bound(s.begin(), s.end(), x) - s.begin();
    }
    int dct2(T x) {
        return upper_bound(s.begin(), s.end(), x) - s.begin();
    }
    vector<T> v, s; // array, sorted
    vector<int> cnt;
    StaticKth(const vector<T> &v_) {
        s = v = v_;
        sort(s.begin(), s.end());
        s.resize(unique(s.begin(), s.end()) - s.begin());
        cnt.resize(s.size());
        init(s.size());
        for (int i = 0; i < v.size(); i++) {
            createVersion(i);
            int d = dct(v[i]);
            modify(i + 1, d, ++cnt[d]);
        }
    }
    int work(int a, int b, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return 0;
        if (ql <= l && r <= qr) {
            return nd[b].info - nd[a].info;
        }
        int m = (l + r) / 2;
        return work(nd[a].lc, nd[b].lc, l, m, ql, qr) + work(nd[a].rc, nd[b].rc, m, r, ql, qr);
    }
    int work(int l, int r, int ql, int qr) { // [l, r), k > 0
        return work(rt[l], rt[r], 0, n, ql, qr);
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
    StaticKth<int> seg(a);
    while (q--) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        int ans = seg.work(a - 1, b, seg.dct(c), seg.dct2(d));
        cout << ans << "\n";
    }
    return 0;
}