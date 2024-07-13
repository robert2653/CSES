#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> c(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    vector<int> dp(x + 1);
    dp[0] = 1;
    
    for (int i = 1; i <= x; i++) {
        for (int j = 0; j < n; j++) {
            if (i - c[j] >= 0) {
                dp[i] = (dp[i] + dp[i - c[j]]) % Mod;
            }
        }
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