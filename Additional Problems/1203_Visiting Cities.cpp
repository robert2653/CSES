#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m;
    cin >> n >> m;
    vector g(n, vector<pair<int, ll>>());
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        ll w;
        cin >> w;
        g[u].emplace_back(v, w);
    }
    vector<ll> dis(n, 4e18);
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    pq.emplace(0, 0);
    vector<int> par(n);
    dis[0] = 0;
    while (!pq.empty()) {
        auto [dist, u] = pq.top();
        pq.pop();
        if (dis[u] < dist) continue;
        for (auto [v, w] : g[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                par[v] = u;
                pq.emplace(dis[v], v);
            }
        }
    }
    vector<int> order;
    int now = n - 1;
    while (now != 0) {
        order.push_back(now);
        now = par[now];
    }
    order.push_back(0);
    reverse(order.begin(), order.end());
    
    cout << order.size() << "\n";
    for (int x : order) {
        cout << x + 1 << " ";
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