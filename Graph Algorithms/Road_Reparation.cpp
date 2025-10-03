#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--, v--;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
    vector<bool> vis(n);
    ll ans = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [w, u] = pq.top();
        pq.pop();
        if (vis[u]) {
            continue;
        }
        vis[u] = true;
        ans += w;
        for (auto [v, w] : g[u]) {
            if (!vis[v]) {
                pq.emplace(w, v);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            cout << "IMPOSSIBLE" << '\n';
            return 0;
        }
    }
    cout << ans << "\n";

    return 0;
}