#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Info {
    static constexpr int DIM = 2;
    array<int, DIM> x, L, R;
    ll distl, distr;
    ll f(const Info &i) {
        ll ret = 0;
        if (i.R[0] > x[0]) ret += i.R[0] - x[0];
        if (i.L[0] < x[0]) ret += x[0] - i.L[0];
        if (i.R[1] > x[1]) ret += i.R[1] - x[1];
        if (i.L[1] < x[1]) ret += x[1] - i.L[1];
        return ret;
    }
    void pull(const Info &l, const Info &r) {
        distl = f(l), distr = f(r);
    }
};
struct KDTree {
    static constexpr int DIM = Info::DIM;
    vector<Info> info;
    vector<int> rt, l, r, p;
    int n = 0, lg;
    KDTree(int n) : info(1), lg(__lg(n)), l(n + 1), r(n + 1) {
        rt.resize(lg + 1);
    }
    void pull(int p) {
        info[p].L = info[p].R = info[p].x;
        info[p].pull(info[l[p]], info[r[p]]);
        for (int ch : {l[p], r[p]}) {
            if (!ch) continue;
            for (int k = 0; k < DIM; k++) {
                info[p].L[k] = min(info[p].L[k], info[ch].L[k]);
                info[p].R[k] = max(info[p].R[k], info[ch].R[k]);
            }
        }
    }
    int rebuild(int l, int r) {
        if (r == l) return 0;
        int m = (l + r) / 2;
        array<double, DIM> av = {}, va = {};
        for (int i = l; i < r; i++) {
            for (int d = 0; d < DIM; d++) {
                av[d] += info[p[i]].x[d];
            }
        }
        for (int d = 0; d < DIM; d++) {
            av[d] /= (double)(r - l);
        }
        for (int i = l; i < r; i++) {
            for (int d = 0; d < DIM; d++) {
                va[d] += (info[p[i]].x[d] - av[d]);
            }
        }
        int dep = max_element(va.begin(), va.end()) - va.begin();
        nth_element(p.begin() + l, p.begin() + m, p.begin() + r,
            [&](int x, int y) { return info[x].x[dep] < info[y].x[dep]; });
        int x = p[m];
        this->l[x] = rebuild(l, m);
        this->r[x] = rebuild(m + 1, r);
        pull(x);
        return x;
    }
    void append(int &x) {
        if (!x) return;
        p.push_back(x);
        append(l[x]);
        append(r[x]);
        x = 0;
    }
    void addNode(const Info &i) {
        p.assign(1, info.size());
        info.push_back(i);
        for (int j = 0;; j++) {
            if (!rt[j]) {
                rt[j] = rebuild(0, p.size());
                break;
            } else {
                append(rt[j]);
            }
        }
    }
    ll ans = 0;
    ll dist(int a, int b) {
        return 0LL + abs(info[a].x[0] - info[b].x[0]) + abs(info[a].x[1] - info[b].x[1]);
    }
    void query(int p, int x) {
        if (!p) return;
        if (p != x) ans = max(ans, dist(x, p));
        ll distl = info[x].f(info[l[p]]);
        ll distr = info[x].f(info[r[p]]);
        if (distl > ans && distr > ans) {
            if (distl < distr) {
                query(l[p], x);
                if (distr > ans) query(r[p], x);
            } else {
                query(r[p], x);
                if (distl > ans) query(l[p], x);
            }
        } else {
            if (distl > ans) query(l[p], x);
            if (distr > ans) query(r[p], x);
        }
    }
    void query(int x) {
        for (int i = 0; i <= lg; i++) {
            query(rt[i], x);
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();

    int n;
    cin >> n;
    KDTree kt(n);
    // query mxdis of added point
    for (int i = 1; i <= n; i++) {
        Info info;
        cin >> info.x[0] >> info.x[1];
        kt.addNode(info);
        kt.query(i);
        cout << kt.ans << "\n";
    }
    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}