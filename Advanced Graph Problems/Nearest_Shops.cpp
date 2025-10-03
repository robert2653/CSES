#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> g(n);
    vector<int> st(k);
    for (int i = 0; i < k; i++) {
        cin >> st[i];
        st[i]--;
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    queue<tuple<int, int, int>> que; // dis, now, src
    vector<map<int, int>> dis(n);  // 
    for (auto x : st) {
        que.emplace(0, x, x);
        dis[x][x] = 0;
    }
    while (!que.empty()) {
        auto [d, u, src] = que.front();
        que.pop();
        for (auto v : g[u]) {
            if (dis[v].find(src) != dis[v].end() || dis[v].size() == 2) {
                continue;
            }
            dis[v][src] = d + 1;
            que.emplace(d + 1, v, src);
        }
    }
    for (int i = 0; i < n; i++) {
        int ans = n;
        for (auto [src, d] : dis[i]) {
            if (src != i) {
                ans = min(ans, d);
            }
        }
        cout << (ans == n ? -1 : ans) << " ";
    }
    return 0;
}