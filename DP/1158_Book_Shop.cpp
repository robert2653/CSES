#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, x;
    cin >> n >> x;
    vector<int> p(n), w(n);

    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }

    vector<int> dp(x + 1);
    for (int i = 0; i < n; i++) {
        for (int j = x; j >= 0; j--) {
            if (j - p[i] >= 0) {
                dp[j] = max(dp[j], dp[j - p[i]] + w[i]);
            }
        }
        // for (auto j : dp) cerr << j << " ";
        // cerr << "\n";
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