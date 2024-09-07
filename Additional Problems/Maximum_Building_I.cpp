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

    vector<int> h(m);
    int ans = 0;
    for (int i = 0; i < n; i++) {
        vector<pair<int, int>> stk;
        for (int j = 0; j < m; j++) {
            if (g[i][j] == '.') {
                h[j]++;
            } else {
                h[j] = 0;
            }
            int l = j;
            while (!stk.empty() && stk.back().second > h[j]) {
                ans = max(ans, (j - stk.back().first) * stk.back().second);
                l = stk.back().first;
                stk.pop_back();
            }
            stk.emplace_back(l, h[j]);
        }
        while (!stk.empty()) {
            ans = max(ans, (m - stk.back().first) * stk.back().second);
            stk.pop_back();
        }
    }
    cout << ans << "\n";

    return 0;
}