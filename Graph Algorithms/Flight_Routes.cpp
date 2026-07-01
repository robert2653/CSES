#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

void solve() {
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        g[u].emplace_back(v, w);
    }
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<>> pq;
    pq.emplace(0, 0);
    vector<vector<ll>> dis(n);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (dis[u].size() == k) continue;
        dis[u].push_back(d);
        for (auto [v, w] : g[u]) {
            if (dis[v].size() < k) pq.emplace(d + w, v);
        }
    }
    for (int i = 0; i < k; i++) {
        cout << dis[n - 1][i] << " \n"[i == k - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();
    
    return 0;
}