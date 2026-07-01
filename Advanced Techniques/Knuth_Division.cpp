#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }
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

void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    vector<ll> pre(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pre[i + 1] = pre[i] + a[i];
    }
    vector<vector<int>> opt(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        opt[i][i] = i;
    }
    const ll inf = 4E18;
    vector<vector<ll>> dp(n, vector<ll>(n));
    for (int l = n - 2; l >= 0; l--) {
        for (int r = l + 1; r < n; r++) {
            dp[l][r] = inf;
            for (int k = opt[l][r - 1]; k <= min(r - 1, opt[l + 1][r]); k++) {
                ll cost = dp[l][k] + dp[k + 1][r] + pre[r + 1] - pre[l];
                if (cost < dp[l][r]) {
                    dp[l][r] = cost;
                    opt[l][r] = k;
                }
            }
        }
    }
    cout << dp[0][n - 1] << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}