#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int inf = 1e9;

void solve() {
    int a, b;
    cin >> a >> b;
    // dp[i][j] 代表 a * b 的最小刀數，如果在 k 的地方下一刀
    // 則有 dp[i][j] = min(dp[i - k][j] + dp[k][j], dp[i][j - k] + dp[i][k]) + 1
    vector dp(a + 1, vector<int>(b + 1, inf));
    for (int i = 0; i <= min(a, b); i++) dp[i][i] = 0;
    for (int i = 1; i <= a; i++) {
        for (int j = 1; j <= b; j++) {
            for (int k = 1; k < i; k++) {
                dp[i][j] = min(dp[i][j], dp[i - k][j] + dp[k][j] + 1);
            }
            for (int k = 1; k <= j; k++) {
                dp[i][j] = min(dp[i][j], dp[i][j - k] + dp[i][k] + 1);
            }
        }
    }
    cout << dp[a][b] << "\n";
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