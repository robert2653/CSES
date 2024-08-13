#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m; cin >> n >> m;
    vector<int> in(n), out(n);
    out[0]--; in[n - 1]--;
    vector<set<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        out[u]++; in[v]++;
        g[u].insert(v);
    }
    for (int i = 0; i < n; i++) {
        if (in[i] != out[i]) {
            cout << "IMPOSSIBLE\n";
            return;
        }
    }

    vector<int> ans;
    auto dfs = [&](auto &&self, int u) -> void {
        while (g[u].size()) {
            int v = *g[u].begin();
            g[u].erase(v);
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