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

struct Bipartite_Matching { // 1-based
    int n, m; vector<vector<int>> adj;
    vector<int> match, vis;
    Bipartite_Matching(int n, int m, vector<vector<int>> &adj) {
        this->n = n;
        this->m = m;
        this->adj = adj;
        match.assign(n + m + 1, -1);
        vis.assign(n + m + 1, 0);
    }
    pair<int, vector<pair<int, int>>> matching() {
        int cnt = 0; vector<pair<int, int>> ans;
        auto dfs = [&](auto self, int u) -> bool {
            for (int v : adj[u]) {
                if (vis[v] == 0) {
                    vis[v] = 1;
                    if (match[v] == -1 || self(self, match[v])) {
                        match[v] = u;
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
        for (int i = n + 1; i <= n + m; i++) {
            if (match[i] != -1) {
                cnt += 1;
            }
        }
        for (int i = n + 1; i <= n + m; i++) {
            if (match[i] != -1) {
                ans.push_back({match[i], i - n});
            }
        }
        return { cnt, ans };
    }
};
void solve(){
    int n, m, e; cin >> n >> m >> e;
    vector<vector<int>> adj(n + m + 1);
    for (int i = 1; i <= e; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v + n);
        adj[v + n].push_back(u);
    }
    Bipartite_Matching bip(n, m, adj);
    auto [cnt, ans] = bip.matching();
    cout << cnt << "\n";
    for (auto [u, v] : ans) {
        cout << u << " " << v << "\n";
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