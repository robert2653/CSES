#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; ++i) {
        cin >> g[i];
    }
    int dp[n][m][3][3] {};
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int ci = 0; ci < 3; ci++) {
                for (int cj = 0; cj < 3; cj++) {
                    dp[i][j][ci][cj] = -1;
                }
            }
        }
    }
    for (int i = 0; i < 3; i++) {
        if (i != g[0][0] - 'A') {
            dp[0][0][0][0] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int ci = 0; ci < 3; ci++) { // 上面
                for (int cj = 0; cj < 3; cj++) { // 左邊
                    for (int ck = 0; ck < 3; ck++) { // 目前
                        if (i == 0 && j == 0 || ci == ck || cj == ck || ck == g[i][j] - 'A') continue;
                        if (i == 0) {
                            if (dp[i][j - 1][cj][0] != -1) {
                                dp[i][j][ci][cj] = max(dp[i][j][ci][cj], dp[i][j - 1][cj][ck] + ck);
                            }
                        }
                    }
                }
            }
        }
    }
    return 0;
}