#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

// https://hackmd.io/@tmting39/H1yvegOYn#Counting-Tilings

int findBit(int x) {
    return (1 << x);
}
void solve() {
    int n, m;
    cin >> n >> m;
    vector dp(m, vector<vector<int>>(n, vector<int>(findBit(n))));
    dp[0][0][findBit(n) - 2] = 1;
    // i - 2 行填滿，i - 1 行填 j 個，前 n 個排列方式由 bit 表示
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            for (int mask = 0; mask < findBit(n); mask++) {
                if (j == 0) {
                    if (i > 0) dp[i][0][mask] = dp[i - 1][n - 1][mask ^ 1];
                    continue;
                }
                if (mask & findBit(j)) { // (i, j) 有放
                    (dp[i][j][mask] += dp[i][j - 1][mask ^ findBit(j)]) %= Mod;
                    // 橫放
                    if ((mask & findBit(j - 1))) { // 直放
                        (dp[i][j][mask] += dp[i][j - 1][mask ^ findBit(j - 1)]) %= Mod;
                    }
                } else {
                    dp[i][j][mask] = dp[i][j - 1][mask ^ findBit(j)];
                }
            }
        }
    }
    cout << dp[m - 1][n - 1][findBit(n) - 1] << "\n";
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