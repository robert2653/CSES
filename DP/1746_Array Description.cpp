#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int Mod = 1e9 + 7;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> dp(x + 2);
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (a[0] == 0) {
        fill(dp.begin() + 1, dp.begin() + x + 1, 1);
    } else {
        dp[a[0]] = 1;
    }

    for (int i = 1; i < n; i++) {
        vector<int> cur(x + 2);
        if (a[i] == 0) {
            for (int j = 1; j <= x; j++) {
                for (int d : {-1, 0, 1}) {
                    cur[j] = (cur[j] + dp[j + d]) % Mod;
                }
            }
        } else {
            for (int d : {-1, 0, 1}) {
                // cerr << a[i] + d << "\n";
                cur[a[i]] = (cur[a[i]] + dp[a[i] + d]) % Mod;
            }
        }
        // for (auto j : cur) cerr << j << " ";
        // cerr << "\n";
        swap(dp, cur);
    }

    int ans = 0;
    for (int i = 1; i <= x; i++) {
        ans = (ans + dp[i]) % Mod;
    }

    cout << ans << "\n";
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