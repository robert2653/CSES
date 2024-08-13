#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> deg(n);
    vector<set<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        deg[u]++; deg[v]++;
        g[u].insert(v);
        g[v].insert(u);
    }
    for (int i = 0; i < n; i++) {
        if (deg[i] & 1) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }
    vector<int> ans;
    auto dfs = [&](auto &&self, int u) -> void {
        while (g[u].size()) {
            int v = *g[u].begin();
            g[u].erase(v);
            g[v].erase(u);
            self(self, v);
        }
        ans.push_back(u);
    };
    dfs(dfs, 0);
    reverse(ans.begin(), ans.end());
    if (ans.size() != m + 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    for (auto x : ans) cout << x + 1 << " ";
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