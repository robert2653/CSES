#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

void solve() {
    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    vector dp(n + 2, vector<int>(n + 2));
    if (g[0][0] == '.') dp[1][1] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j] == '.') {
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i][j + 1]) % Mod;
                dp[i + 1][j + 1] = (dp[i + 1][j + 1] + dp[i + 1][j]) % Mod;
            }
        }
    }

    cout << dp[n][n] << "\n";
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