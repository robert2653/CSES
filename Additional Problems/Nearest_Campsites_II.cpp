#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// K-D tree solution
template<class Info>
struct KDTree { // 1-indexed
    static constexpr int DIM = Info::DIM;
    int n, rt;
    vector<Info> info;
    vector<int> l, r;
    KDTree(const vector<Info> &info) : n(info.size()), info(info), l(n + 1), r(n + 1) {
        rt = rebuild(1, n);
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
        for (int i = l; i < r; i++)
            for (int d = 0; d < DIM; d++)
                av[d] += info[i].x[d];
        for (int d = 0; d < DIM; d++)
            av[d] /= (double)(r - l);
        for (int i = l; i < r; i++)
            for (int d = 0; d < DIM; d++)
                va[d] += (info[i].x[d] - av[d]) * (info[i].x[d] - av[d]);
        int dep = max_element(va.begin(), va.end()) - va.begin();
        nth_element(info.begin() + l, info.begin() + m, info.begin() + r,
            [&](const Info &x, const Info &y) { return x.x[dep] < y.x[dep]; });
        this->l[m] = rebuild(l, m);
        this->r[m] = rebuild(m + 1, r);
        pull(m); return m;
    }
    int dist(Info &i, int b) {
        return abs(i.x[0] - info[b].x[0]) + abs(i.x[1] - info[b].x[1]);
    }
    void query(Info &i, int p) {
        if (!p) return;
        i.mdist = min(i.mdist, dist(i, p));
        int distl = i.f(info[l[p]]);
        int distr = i.f(info[r[p]]);
        if (distl < i.mdist && distr < i.mdist) {
            if (distl < distr) {
                query(i, l[p]);
                if (distr < i.mdist) query(i, r[p]);
            } else {
                query(i, r[p]);
                if (distl < i.mdist) query(i, l[p]);
            }
        } else {
            if (distl < i.mdist) query(i, l[p]);
            if (distr < i.mdist) query(i, r[p]);
        }
    }
    void query(Info &i) {
        query(i, rt);
    }
};
struct Info {
    static constexpr int DIM = 2;
    array<int, DIM> x, L, R;
    int distl, distr, mdist = 2E9;
    int f(const Info &i) {
        int ret = 0;
        if (i.L[0] > x[0]) ret += (i.L[0] - x[0]);
        if (i.R[0] < x[0]) ret += (x[0] - i.R[0]);
        if (i.L[1] > x[1]) ret += (i.L[1] - x[1]);
        if (i.R[1] < x[1]) ret += (x[1] - i.R[1]);
        return ret;
    }
    void pull(const Info &l, const Info &r) {
        distl = f(l), distr = f(r);
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();

    int n, q;
    cin >> n >> q;
    vector<Info> info(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> info[i].x[0] >> info[i].x[1];
    }
    KDTree<Info> kt(info);
    while (q--) {
        int x, y;
        cin >> x >> y;
        Info res {{x, y}};
        kt.query(res);
        cout << res.mdist << " \n"[q == 0];
    }

    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}