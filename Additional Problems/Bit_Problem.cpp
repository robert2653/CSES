#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mp[a[i]]++;
    }
    // x | y = x, 代表包含於 x 的 y 個數, 定義為 dp[x][0]
    // x & y = x, 代表包含 x 的 y 個數, 定義為 dp[x][1]
    // x & y != 0, 代表至少有一個位元都為 1 的 y 個數, = n - 與自己相同 - ~dp[x][0]

    int m = __lg(*max_element(a.begin(), a.end())) + 1;

    vector<array<ll, 2>> dp(1 << m);
    for (int i = 0; i < n; i++) {
        dp[a[i]][0] += 1;
        dp[a[i]][1] += 1;
    }
    
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[mask][0] += dp[pre][0];
                dp[pre][1] += dp[mask][1];
            }
        }
    }

    // for (int i = 0; i < 1 << m; i++) {
    //     cerr << "mask: " << i << ", " << dp[i][0] << ", " << dp[i][1] << "\n";
    // }

    for (int i = 0; i < n; i++) {
        cout << dp[a[i]][0] << " " << dp[a[i]][1] << " " << n - (dp[((1 << m) - 1) ^ a[i]][0]) << "\n";
    }
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