#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> dp(x + 1);
    dp[0] = 1;

    for (int i = 0; i < n; i++) {
        int c;
        cin >> c;
        for (int j = 0; j <= x; j++) {
            if (j - c >= 0) {
                dp[j] = (dp[j] + dp[j - c]) % Mod;
            }
        }
        // for (auto j : dp) cerr << j << " "; cerr << "\n";
    }
    cout << dp[x] << "\n";
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