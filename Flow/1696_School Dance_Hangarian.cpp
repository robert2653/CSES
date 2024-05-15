#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

void solve(){
    int n, m, e; cin >> n >> m >> e;
    vector<vector<int>> adj(n + m + 1);
    for (int i = 1; i <= e; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(n + v);
        adj[n + v].push_back(u);
    }
    vector<int> ans(n + m + 1, -1);
    vector<int> vis(n + m + 1, 0);
    auto dfs = [&](auto self, int u) -> bool {
        for (int v : adj[u]) {
            if (vis[v] == 0) {
                vis[v] = 1;
                if (ans[v] == -1 || self(self, ans[v])) {
                    ans[v] = u;
                    return true;
                }
            }
        }
        return false;
    };
    for (int i = 1; i <= n; i++) {
        fill(all(vis), 0);
        dfs(dfs, i);
    }
    int cnt = 0;
    for (int i = n + 1; i <= n + m; i++) {
        if (ans[i] != -1) {
            cnt += 1;
        }
    }
    cout << cnt << "\n";
    for (int i = n + 1; i <= n + m; i++) {
        if (ans[i] != -1) {
            cout << ans[i] << " " << i - n << "\n";
        }
    }
}
signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}