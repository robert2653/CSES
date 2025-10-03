#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n), b(m);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    vector<vector<int>> dp(n + 1, vector<int>(m + 1));
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (a[i - 1] == b[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }
    int l = dp[n][m];
    vector<int> ans(l);
    cout << l << "\n";
    while (n >= 1 && m >= 1) {
        if (a[n - 1] == b[m - 1]) {
            ans[l - 1] = a[n - 1];
            n--, m--, l--;
        } else {
            if (dp[n - 1][m] > dp[n][m - 1]) {
                n--;
            } else {
                m--;
            }
        }
    }
    for (auto i : ans) {
        cout << i << " ";
    }
    return 0;
}