#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    int lg = __lg(n);
    const int N = 1E6;
    vector<vector<int>> dp(N, vector<int>(lg + 1, N));
    // 從 i 開始看 2^j 個電影的最早結束時間

    vector<vector<int>> g(N);
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        g[l].push_back(r);
    }
    for (int i = N - 1, mn = N; i >= 0; i--) {
        for (int j : g[i]) {
            chmin(mn, j);
        }
        dp[i][0] = mn;
    }
    for (int j = 1; j <= lg; j++) {
        for (int i = 0; i < N; i++) {
            if (dp[i][j - 1] < N) dp[i][j] = dp[dp[i][j - 1]][j - 1];
        }
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int ans = 0;
        for (int j = lg; j >= 0; j--) {
            if (dp[l][j] <= r) {
                ans += 1 << j;
                l = dp[l][j];
            }
        }
        cout << ans << "\n";
    }
    
    return 0;
}