#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int mod = 1e9 + 7;

void solve(){
    int n, a, b; cin >> n >> a >> b;
    vector dp(n + 1, vector<double>(n * 6 + 1));
    dp[0][0] = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n * 6; j++) {
            for (int k = 1; k <= 6; k++) {
                if (j - k >= 0) {
                    dp[i][j] += dp[i - 1][j - k] / 6.0;
                }
            }
        }
    }
    double ans = 0;
    for (int i = a; i <= b; i++) {
        ans += dp[n][i];
    }
    ans *= 1e7;
    int tmp = ans;
    if (tmp % 10 >= 5) tmp = tmp / 10 + 1;
    else tmp = tmp / 10;
    ans = (double)tmp / 1e6;
    cout << fixed << setprecision(6) << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}