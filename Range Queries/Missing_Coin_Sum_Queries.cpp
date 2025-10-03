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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

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
    return 0;
}