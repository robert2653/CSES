#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll Mod = 1E9 + 7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<vector<int>> g(n);
    vector<int> dp(n, -1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        g[u].push_back(v);
    }
    auto rec = [&](auto rec, int u) -> int {
        if (dp[u] != -1) {
            return dp[u];
        }
        dp[u] = 0;
        for (int v : g[u]) {
            dp[u] = (dp[u] + rec(rec, v)) % Mod;
        }
        return dp[u];
    };
    dp[n - 1] = 1;
    cout << rec(rec, 0) << '\n';
    return 0;
}