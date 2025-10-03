#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
constexpr ll inf = 1E18;
 
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
    }
    
    vector<ll> dis(n * 2, -1);
    priority_queue<tuple<ll, int, int>, vector<tuple<ll, int, int>>, greater<tuple<ll, int, int>>> pq;
    pq.emplace(0, 0, 0);
    while (!pq.empty()) {
        auto [d, u, c] = pq.top();
        pq.pop();
        if (dis[u] != -1) continue;
        dis[u] = d;
        u /= 2;
        for (auto [v, w] : g[u]) {
            ll ndis = d + w;
            int nv = v * 2 + c;
            pq.emplace(ndis, nv, c);
            if (!c) {
                ndis = d + w / 2;
                nv = v * 2 + 1;
                pq.emplace(ndis, nv, 1);
            }
        }
    }
    cout << dis[n * 2 - 1] << "\n";
    return 0;
}