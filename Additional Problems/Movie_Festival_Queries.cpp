#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// dpi,j​ 代表從時間 $i$ 開始，看 $2^j$ 個movie的最短結束時間
// 倍增的轉移：$dp_{i, j} = dp_{dp_{i, j - 1}, j - 1}$
constexpr int inf = 1E9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    const int N = 1E6;
    
    int n, q;
    cin >> n >> q;
    int m = __lg(n);
    // cerr << m << "\n";
    vector<vector<int>> dp(N + 1, vector<int>(m + 1, inf));

    vector<vector<int>> a(N + 1);
    for (int i = 0; i < n; i++) {
        int f, t;
        cin >> f >> t;
        a[f].push_back(t);
    }
    priority_queue<int, vector<int>, greater<int>> pq;
    for (int i = N; i >= 0; i--) {
        for (int j : a[i]) {
            pq.push(j);
        }
        if (!pq.empty()) {
            dp[i][0] = pq.top();
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 0; j <= N; j++) {
            if (dp[j][i - 1] != inf) {
                dp[j][i] = dp[dp[j][i - 1]][i - 1];
            }
        }
    }

    while (q--) {
        int f, t;
        cin >> f >> t;
        int ans = 0;
        for (int i = m; i >= 0; i--) {
            if (dp[f][i] <= t) {
                f = dp[f][i];
                ans |= 1 << i;
            }
        }
        cout << ans << "\n";
    }



    return 0;
}