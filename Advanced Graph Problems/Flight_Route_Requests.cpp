#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    vector<int> ind(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].emplace_back(v, 1);
        g[v].emplace_back(u, 0);
        ind[v]++;
    }
    vector<int> vis(n), cc;
    auto dfs = [&](auto self, int u) -> void {
        vis[u] = 1;
        cc.push_back(u);
        for (auto [v, _] : g[u]) {
            if (!vis[v]) {
                self(self, v);
            }
        }
    };
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        cc.clear();
        dfs(dfs, i);
        queue<int> que;
        int topo = 0;
        for (auto j : cc) {
            if (ind[j] == 0) {
                que.push(j);
            }
        }
        while (!que.empty()) {
            int u = que.front();
            que.pop();
            topo++;
            for (auto [v, ord] : g[u]) {
                if (ord == 1) {
                    ind[v]--;
                    if (ind[v] == 0) {
                        que.push(v);
                    }
                }
            }
        }
        ans += cc.size() - (topo == cc.size());
    }
    cout << ans << "\n";
    return 0;
}