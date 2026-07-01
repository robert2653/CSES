#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<pair<int, ll>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        ll w;
        cin >> u >> v >> w;
        g[u - 1].emplace_back(v - 1, w);
    }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;

    vector<ll> dis(n, -1);
    dis[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dis[u]) {
            continue;
        }
        for (auto [v, w] : g[u]) {
            if (dis[v] == -1 || dis[v] > d + w) {
                dis[v] = d + w;
                pq.emplace(dis[v], v);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        cout << dis[i] << " \n"[i == n - 1];
    }

    return 0;
}