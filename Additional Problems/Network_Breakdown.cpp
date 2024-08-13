#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct DSU {
    int n;
    vector<int> boss, siz;
    DSU() {}
    DSU(int n_) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        boss.resize(n);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n, 1);
    }
    int find_boss(int x) {
        if (boss[x] == x) return x;
        return boss[x] = find_boss(boss[x]);
    }
    bool same(int x, int y) {
        return find_boss(x) == find_boss(y);
    }
    bool merge(int x, int y) {
        x = find_boss(x);
        y = find_boss(y);
        if (x == y) {
            return false;
        }
        if(siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        boss[y] = x;
        n--;
        return true;
    }
    int size(int x) {
        return siz[find_boss(x)];
    }
};

void solve() {
    int n, m, q; cin >> n >> m >> q;
    DSU dsu(n);
    vector<pair<int, int>> query;
    set<pair<int, int>> init;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        init.insert({u, v});
    }
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        init.erase({u, v});
        init.erase({v, u});
        query.emplace_back(u, v);
    }
    for (auto [u, v] : init) {
        dsu.merge(u, v);
    }
    vector<int> ans;
    reverse(query.begin(), query.end());
    for (auto [u, v] : query) {
        ans.push_back(dsu.n);
        dsu.merge(u, v);
    }
    reverse(ans.begin(), ans.end());
    for (auto x : ans) cout << x << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}