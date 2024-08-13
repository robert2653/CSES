#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    vector<vector<char>> g(8, vector<char>(8));
    vector<int> col_used(8, false);
    vector<int> diff_used(16, false); // 看左上右下 (r + c) == (r - 1 + c - 1)
    vector<int> sum_used(16, false); // 看左下右上 (r + c) == (r + 1 + c - 1)

    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            cin >> g[i][j];
        }
    }
    int ans = 0;
    auto dfs = [&](auto &&self, int r) -> void {
        if (r == 8) {
            ans++;
            return;
        }
        for (int c = 0; c < 8; c++) {
            if (col_used[c] || g[r][c] != '.' || diff_used[r - c + 8] || sum_used[r + c]) continue;
            col_used[c] = true;
            diff_used[r - c + 8] = true;
            sum_used[r + c] = true;
            self(self, r + 1);
            col_used[c] = false;
            diff_used[r - c + 8] = false;
            sum_used[r + c] = false;
        }
    };
    dfs(dfs, 0);
    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}