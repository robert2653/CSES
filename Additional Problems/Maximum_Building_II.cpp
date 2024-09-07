#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 1 1 1 0 1 0 1
// 2 0 2 1 2 1 2
// 3 1 3 2 3 2 3
// 4 2 4 3 4 3 0

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    // 加個前綴差分
    struct node {
        int h, l;
    };
    vector<vector<int>> pref(n + 2, vector<int>(m + 2));

    vector<int> h(m);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<node> stk;
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                h[j]++;
            } else {
                h[j] = 0;
            }
            int l = j;
            bool flag = false;
            while (!stk.empty() && stk.back().h > h[j]) {
                flag = true;
                // ans = max(ans, (j - stk.back().first) * stk.back().second);
                int xh = stk.back().h;
                int xw = j - stk.back().l;
                pref[1][1] += 1;
                pref[xh + 1][1] -= 1;
                pref[1][xw + 1] -= 1;
                pref[xh + 1][xw + 1] += 1;
                l = stk.back().l;
                stk.pop_back();
                cerr << i << " " << j << " " << xh << " " << xw << "\n";
            }

            if (g[i][j] == '.' && flag) {
                pref[1][l + 2] += 1;
                pref[1][j + 2] -= 1;
                pref[h[j] + 1][l + 2] -= 1;
                pref[h[j] + 1][j + 2] += 1;
            }
            
            stk.push_back({h[j], l});
        }
        while (!stk.empty() && stk.back().h > 0) {
            int xh = stk.back().h;
            int xw = m - stk.back().l;
            pref[1][1] += 1;
            pref[xh + 1][1] -= 1;
            pref[1][xw + 1] -= 1;
            pref[xh + 1][xw + 1] += 1;
            // ans = max(ans, (m - stk.back().first) * stk.back().second);
            stk.pop_back();
            cerr << i << " " << m << " " << xh << " " << xw << "\n";
        }
    }
    // cout << ans << "\n";

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            pref[i][j] += pref[i - 1][j] + pref[i][j - 1] - pref[i - 1][j - 1];
            cout << pref[i][j] << " \n"[j == m];
        }
    }

    return 0;
}