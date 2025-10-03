#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<vector<int>> g[2];
    for (int i = 0; i < 2; i++) {
        g[i].resize(n);
        for (int j = 1; j < n; j++) {
            int u, v;
            cin >> u >> v;
            u--, v--;
            g[i][u].push_back(v);
            g[i][v].push_back(u);
        }
    }
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
    if (dfs(dfs, 0, -1, g[0]) == dfs(dfs, 0, -1, g[1])) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}