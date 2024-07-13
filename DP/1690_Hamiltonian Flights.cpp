#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

int findBit(int x) {
    return (1 << x);
}

void solve() {
    int n, m; cin >> n >> m;
    vector adj(n, vector<int>());
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[--v].push_back(--u);
    }
    // 以...為終點，走過...
    vector dp(n, vector<int>(findBit(n)));
    dp[0][1] = 1;
    for (int mask = 1; mask < findBit(n); mask++) {
        if ((mask & 1) == 0) continue;
        for (int i = 0; i < n; i++) {
            if ((mask & findBit(i)) == 0) continue;
            if (i == n - 1 && mask != findBit(n) - 1) continue;
            int pre_mask = mask ^ findBit(i);
            for (int j : adj[i]) {
                if ((pre_mask & findBit(j)) == 0) continue;
                dp[i][mask] = (dp[i][mask] + dp[j][pre_mask]) % Mod;
            }
        }
    }
    cout << dp[n - 1][findBit(n) - 1] << "\n";
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