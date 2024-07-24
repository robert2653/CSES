#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int inf = 1E9;

void solve() {
    int n, x; cin >> n >> x;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<array<int, 2>> dp(1 << n);
    dp[0][0] = 1; // 次數、已使用人數
    for (int mask = 1; mask < 1 << n; mask++) {
        dp[mask][0] = dp[mask][1] = 1e9;
        for (int i = 0; i < n; i++) {
            if ((mask >> i & 1) == 0) continue;
            int pre_mask = mask ^ (1 << i);
            if (dp[pre_mask][1] + a[i] <= x) {
                if (dp[pre_mask][0] < dp[mask][0] || dp[pre_mask][0] == dp[mask][0] && dp[pre_mask][1] + a[i] < dp[mask][1]) {
                    dp[mask][0] = dp[pre_mask][0];
                    dp[mask][1] = dp[pre_mask][1] + a[i];
                }
            } else if (dp[pre_mask][0] + 1 < dp[mask][0] || dp[pre_mask][0] + 1 == dp[mask][0] && a[i] < dp[mask][1]) {
                dp[mask][0] = dp[pre_mask][0] + 1;
                dp[mask][1] = a[i];
            }
        }
    }
    cout << dp[(1 << n) - 1][0] << "\n";
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