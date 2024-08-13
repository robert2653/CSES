#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int mod = 1e9 + 7;

void solve(){
    int n; cin >> n;
    vector<int> dp(n + 1);
    dp[1] = 0; dp[2] = 1;
    for (int i = 3; i <= n; i++){
        dp[i] = ((dp[i - 1] + dp[i - 2]) % mod) * (i - 1) % mod;
    }
    cout << dp[n] << "\n";
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