#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define int long long
using namespace std;
const int mod = 1e9 + 7;

vector<int> dx = {0, 0, 1, -1};
vector<int> dy = {1, -1, 0, 0};
int get_pos_dir_num(int x, int y) {
    int dir_num = 0;
    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) continue;
        dir_num++;
    }
    return dir_num;
}
void solve() {
    vector posibility(8, vector<double>(8, 1));
    int k; cin >> k;
    for (int x = 0; x < 8; x++) {
        for (int y = 0; y < 8; y++) {
            vector dp(8, vector<double>(8));    // dp[i][j] 代表，動 step 步時，對於 (x, y) 點的 robot，會在它上面的概率
            dp[x][y] = 1;
            for (int step = 0; step < k; step++) {
                vector nxt(8, vector<double>(8));
                for (int i = 0; i < 8; i++) {
                    for (int j = 0; j < 8; j++) {
                        int dir_num = get_pos_dir_num(i, j);
                        for (int d = 0; d < 4; d++) {
                            int nx = i + dx[d];
                            int ny = j + dy[d];
                            if (nx < 0 || nx >= 8 || ny < 0 || ny >= 8) continue;
                            nxt[nx][ny] += dp[i][j] / dir_num;  // 要除上當前點可能的下一步數
                        }
                    }
                }
                dp = nxt;
            }
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8; j++) {
                    // 最後的結果當然是，對於每個 (x, y) robot，最後不在他位置上的概率相乘
                    posibility[i][j] *= (1 - dp[i][j]);
                }
            }
        }
    }
    double ans = 0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // random variable 是 1
            ans += posibility[i][j];
        }
    }
    cout << fixed << setprecision(6) << ans << "\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}