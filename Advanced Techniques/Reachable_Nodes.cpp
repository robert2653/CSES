#include <bits/stdc++.h>
#pragma GCC target("popcnt")

using namespace std;
using ll = long long;
constexpr int N = 5e4;

void solve() {
    int n, m; cin >> n >> m;
    vector g(n, vector<int>());
    vector rev(n, vector<int>());
    vector<int> in(n);
    vector<bitset<50000>> dp(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        in[v]++;
        rev[v].push_back(u);
    }

    queue<int> q;
    // vector<int> ans(n, 1);
    vector<int> order;
    order.reserve(n);

    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order.push_back(u);
        for (auto v : g[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    reverse(order.begin(), order.end());
    // for (auto i : order) cerr << i << " ";
    for (auto u : order) {
        dp[u].set(u);
        // ans[u] = dp[u].count();
        for (auto v : rev[u]) {
            dp[v] |= dp[u];
        }
    }

    for (int i = 0; i < n; i++) {
        // cout << ans[i] << " ";
        cout << dp[i].count() << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    // freopen("in.txt", "r", stdin);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}