#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr ll inf = 4e18;

void solve() {
    int n, m; cin >> n >> m;
    vector g(n, vector<pair<int, int>>());
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        u--; v--; g[u].emplace_back(v, -w);
    }
    vector<ll> dis(n, inf);
    vector<bool> vis(n);
    queue<int> q;
    vector<int> cnt(n); // 鬆弛幾次
    q.push(0); dis[0] = 0; vis[0] = true;

    vector<bool> vis2(n);
    auto dfs = [&](auto &&self, int u) -> void {
        if (vis2[u]) return;
        vis2[u] = true;
        for (auto [v, w] : g[u]) {
            self(self, v);
        }
    };
    while (!q.empty()) {
        int u = q.front(); q.pop();
        vis[u] = false;
        for (auto [v, w] : g[u]) {
            ll ndis = dis[u] + w;
            if (dis[v] > ndis) {
                dis[v] = ndis;
                cnt[v]++;
                if (cnt[v] >= n) {
                    dfs(dfs, v);
                    continue;
                }
                if (!vis[v]) {
                    q.push(v);
                    vis[v] = true;
                }
            }
        }
    }
    if (!vis2[n - 1]) {
        cout << -dis[n - 1] << "\n";
    } else {
        cout << -1 << "\n";
    }
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