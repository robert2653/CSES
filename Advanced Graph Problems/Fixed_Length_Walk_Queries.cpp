#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    vector<vector<array<int, 2>>> mind(n, vector<array<int, 2>>(n, {-1, -1}));
    for (int i = 0; i < n; i++) {
        queue<pair<int, int>> que;
        que.emplace(0, i);
        mind[i][i][0] = 0;
        while (!que.empty()) {
            auto [d, u] = que.front();
            que.pop();
            for (auto v : g[u]) {
                int nd = d + 1;
                if (mind[i][v][nd % 2] == -1) {
                    mind[i][v][nd % 2] = nd;
                    que.emplace(nd, v);
                }
            }
        }
    }
    while (q--) {
        int u, v, d;
        cin >> u >> v >> d;
        if (mind[u - 1][v - 1][d % 2] <= d && mind[u - 1][v - 1][d % 2] != -1) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }
    return 0;
}