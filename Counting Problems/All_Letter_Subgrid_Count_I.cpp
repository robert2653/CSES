#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// L[k][i][j]
// 為了 N=3000，必須開在 global 或 heap 上
vector<vector<vector<int>>> L; 
vector<vector<int>> S_invalid;
vector<vector<int>> dp;
vector<string> g;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    g.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    // 1. & 2. 計算 L 和 S_invalid
    L.resize(k, vector<vector<int>>(n, vector<int>(n)));
    S_invalid.resize(n, vector<int>(n, 0));

    for (int c = 0; c < k; c++) {
        char target = 'A' + c;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (g[i][j] == target) {
                    L[c][i][j] = 0;
                } else {
                    L[c][i][j] = 1;
                    if (i > 0 && j > 0) {
                        L[c][i][j] += min({L[c][i - 1][j], L[c][i][j - 1], L[c][i - 1][j - 1]});
                    }
                }
                // 順便計算 S_invalid
                S_invalid[i][j] = max(S_invalid[i][j], L[c][i][j]);
            }
        }
    }

    // 3. 最終 DP
    ll total_ans = 0;
    dp.resize(n, vector<int>(n, 0));

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            int S_pot = 1;
            if (i > 0 && j > 0) {
                S_pot += min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }

            int S_bad = S_invalid[i][j];

            if (S_pot > S_bad) {
                dp[i][j] = S_pot;
            } else {
                // S_pot <= S_bad
                // S_pot x S_pot 是無效的
                // 最大的有效正方形邊長是 S_bad - 1
                // 但也必須 <= S_pot
                // 綜合起來是 S_bad - 1 (因為 S_pot <= S_bad)
                // 修正：應該是 min(S_pot, S_bad - 1)
                // 不對，就是 S_bad - 1 (因為 S_pot - 1 <= S_bad - 1)
                // 再次修正：就是 S_bad - 1。因為 S_pot 只是「潛在」，S_bad 是「絕對」
                
                // if S_pot=4, S_bad=5. dp = S_bad - 1 = 4.
                // if S_pot=5, S_bad=5. dp = S_bad - 1 = 4.
                dp[i][j] = S_bad - 1;
            }

            // 確保 dp 值不為負
            if (dp[i][j] < 0) {
                dp[i][j] = 0;
            }

            total_ans += dp[i][j];
        }
    }

    cout << total_ans << "\n";
    return 0;
}