#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int x = accumulate(a.begin(), a.end(), 0);
    vector<int> dp(x + 1);
    dp[0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = x; j >= 0; j--) {
            if (j - a[i] >= 0) {
                dp[j] |= dp[j - a[i]];
            }
        }
    }
    cout << accumulate(dp.begin() + 1, dp.end(), 0) << "\n";
    for (int i = 1; i <= x; i++) {
        if (dp[i]) cout << i << " ";
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