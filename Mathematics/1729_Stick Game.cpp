#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define int long long
using namespace std;
const int mod = 1e9 + 7;

void solve() {
    // dp[i] 代表，有 i 根時，A 會贏還是輸
    // 轉移式: 如果有任何 dp[i - k] 是 false，那他就是 true，否則是 false
    // 初始條件: dp[0] = true
    int n; cin >> n;
    int k; cin >> k;
    vector<int> a(k);
    for (int i = 0; i < k; i++) {
        cin >> a[i];
    }
    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++) {
        for (auto p : a) {
            if (i - p >= 0) {
                dp[i] |= !dp[i - p];
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << (dp[i] ? "W" : "L");
    }
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}