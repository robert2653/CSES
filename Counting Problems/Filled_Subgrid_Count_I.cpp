#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    vector<vector<int>> dp(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            char c = g[i][j];
            if (i == 0 || j == 0) {
                dp[i][j] = 1;
            } else {
                if (g[i - 1][j] == c && g[i][j - 1] == c && g[i - 1][j - 1] == c) {
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
                } else {
                    dp[i][j] = 1;
                }
            }
        }
    }
    vector<ll> ans(k);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            ans[g[i][j] - 'A'] += dp[i][j];
        }
    }
    for (int c = 0; c < k; c++) {
        cout << ans[c] << "\n";
    }
    return 0;
}