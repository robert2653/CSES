#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<int> getCen(int n, vector<vector<int>> &g) {
    vector<int> siz(n), res;
    auto getSiz = [&](auto self, int u, int p) -> int {
        siz[u] = 1;
        for (auto v : g[u]) {
            if (v == p) continue;
            siz[u] += self(self, v, u);
        }
        return siz[u];
    };
    getSiz(getSiz, 0, -1);

    auto isCentroid = [&](int u) -> bool {
        for (auto v : g[u]) {
            if (siz[v] < siz[u] && siz[v] * 2 > n) {
                return false;
            }
        }
        return (n - siz[u]) * 2 <= n;
    };
    for (int u = 0; u < n; u++) {
        if (isCentroid(u)) {
            res.push_back(u);
        }
    }
    assert(res.size() <= 2);
    return res;
}

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> t1(n), t2(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        t1[u].push_back(v);
        t1[v].push_back(u);
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        t2[u].push_back(v);
        t2[v].push_back(u);
    }
    vector<int> c1s = getCen(n, t1), c2s = getCen(n, t2);
    int id;
    map<vector<int>, int> mp;
    auto dfs = [&](auto self, int x, int p, vector<vector<int>> &g) -> int {
        vector<int> a;
        for (auto y : g[x]) {
            if (y == p) continue;
            a.push_back(self(self, y, x, g));
        }
        sort(a.begin(), a.end());
        if (!mp.count(a)) {
            mp[a] = id++;
        }
        return mp[a];
    };
    for (auto c1 : c1s) {
        for (auto c2 : c2s) {
            if (dfs(dfs, c1, -1, t1) == dfs(dfs, c2, -1, t2)) {
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;

    while (t--) {
        solve();
    }

    return 0;
}