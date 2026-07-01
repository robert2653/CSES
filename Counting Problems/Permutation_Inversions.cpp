#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int Mod = 1E9 + 7;
int add(int a, int b) { a += b; if (a >= Mod) a -= Mod; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += Mod; return a; }
int mul(int a, int b) { return 1LL * a * b % Mod; }
int power(int a, ll b) {
    int ans = 1;
    for (; b > 0; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(ans, a);
    return ans;
}
// 0 1 1 3 1
// 0 4 1 3 1
// 4 4 3 1 3 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // dp[i][k] = \sum_{j=0}^{i - 1} dp[i - 1][k - j]
    int n, k;
    cin >> n >> k;
    vector<vector<int>> dp(n + 1, vector<int>(k + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        vector<int> pref(k + 1);
        for (int j = 0; j <= k; j++) {
            pref[j] = dp[i - 1][j];
            if (j > 0) pref[j] = add(pref[j], pref[j - 1]);
        }
        for (int j = 0; j <= k; j++) {
            dp[i][j] = pref[j];
            if (j - i >= 0) {
                dp[i][j] = sub(dp[i][j], pref[j - i]);
            }
        }
    }
    cout << dp[n][k] << "\n";
    return 0;
}