#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    queue<int> que;
    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].emplace_back(v, i);
        g[v].emplace_back(u, i);
    }

    vector<int> done(n, 1);
    vector<int> vis(n);
    vector<pair<int, int>> ans(m);
    auto dfs = [&](auto self, int u, int p) -> void {
        vis[u] = 1;
        for (auto [v, id] : g[u]) {
            if (v == p) continue;
            if (vis[v] == 0) {
                self(self, v, u);
                if (done[v]) {
                    ans[id] = {u, v}; // 不要影響到他
                    done[u] ^= 1;
                } else {
                    done[v] = 1;
                    ans[id] = {v, u};
                }
            } else if (vis[v] == 1) {
                done[u] ^= 1;
                ans[id] = {u, v};
            }
        }
        vis[u] = 2;
    };
    for (int i = 0; i < n; i++) {
        if (vis[i] == 0) {
            dfs(dfs, i, -1);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            cout << "IMPOSSIBLE\n";
            return 0;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i].first + 1 << " " << ans[i].second + 1 << "\n";
    }
    return 0;
}