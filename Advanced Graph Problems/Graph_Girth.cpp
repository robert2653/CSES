#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<pair<int, int>> e(m);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
        e[i] = {u, v};
    }

    int ans = n + 1;
    for (auto [s, t] : e) {
        vector<int> dis(n, -1);
        queue<int> que;
        que.push(s);
        dis[s] = 0;
        bool found = false;
        while (!que.empty() && !found) {
            int u = que.front();
            que.pop();
            for (auto v : g[u]) {
                if (dis[v] != -1) continue;
                if (u == s && v == t) continue;
                dis[v] = dis[u] + 1;
                if (v == t) {
                    ans = min(ans, dis[t] + 1);
                    found = true;
                    break;
                }
                que.push(v);
            }
        }
    }
    cout << (ans == n + 1 ? -1 : ans) << "\n";
    return 0;
}