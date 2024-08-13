#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int N = 3e3 + 5;
int n = 0;
constexpr ll inf = 4e18;
// dp[k][j] 代表架了 k 個且最後一個架在 j 的最佳解(只算前 j 個學生)
ll pref[3][N], dp[N][N]; // 1-based
ll get_cost(int l, int r) { // l, r 有架
    int m = (l + r) / 2;
    ll lans = 0, rans = 0;
    lans = pref[1][m] - pref[1][l] - (pref[0][m] - pref[0][l]) * l; // (l, m]
    rans = pref[2][r] - pref[2][m] - (pref[0][r] - pref[0][m]) * (n - r + 1); // (m, r) 28 - 14
    return lans + rans;
}
void DNC(int k, int l, int r, int optl, int optr) {
    if (l > r) return;
    int m = (l + r) >> 1, opt = -1;
    dp[k][m] = inf;
    for (int i = max(k, optl); i <= min(optr, m); i++) {
        // m 預設有架了，選一個架在 i
        ll cur = dp[k - 1][i] + get_cost(i, m);
        if (cur < dp[k][m]) {
            dp[k][m] = cur, opt = i;
        }
    }
    DNC(k, l, m - 1, optl, opt);
    DNC(k, m + 1, r, opt, optr);
}

void solve() {
    int k; cin >> n >> k;
    // first build cost...]
    for (int i = 1; i <= n; i++) {
        ll x; cin >> x;
        pref[0][i] = pref[0][i - 1] + x;
        pref[1][i] = pref[1][i - 1] + i * x;
        pref[2][i] = pref[2][i - 1] + (n - i + 1) * x;
    }

    ll test = get_cost(1, n);
    for (int i = 1; i <= n; i++) {
        dp[1][i] = pref[2][i] - pref[0][i] * (n - i + 1);
    }
    for (int i = 2; i <= k; i++) {
        DNC(i, 1, n, 1, n);
    }
    ll ans = inf;
    for (int i = 1; i <= n; i++) {
        ans = min(ans, dp[k][i] + pref[1][n] - pref[1][i - 1] - (pref[0][n] - pref[0][i - 1]) * i);
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