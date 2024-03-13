#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using pbds_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

// a, b += 1, lca(a, b) -= 1, postorder dp
void solve(){
    int n, q; cin >> n >> q;
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<vector<int>> par(n + 1, vector<int>(18));
    vector<int> depth(n + 1);
    auto dfs = [&](auto self, int u, int pre) -> void {
        for (auto v : tree[u]) {
            if (v == pre) continue;
            par[v][0] = u;  // 2 ^ 0
            depth[v] = depth[u] + 1;
            self(self, v, u);
        }
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i < 18; i++) {
        for (int j = 1; j <= n; j++) {
            par[j][i] = par[par[j][i - 1]][i - 1];
        }
    }
    auto lca = [&](int a, int b) -> int {
        if (depth[a] < depth[b]) swap(a, b);
        int pull = depth[a] - depth[b];
        for (int i = 0; i < 18; i++) {
            if (pull & (1 << i)) {
                a = par[a][i];
            }
        }
        if (a == b) return a;
        for (int i = 17; i >= 0; i--) {
            if (par[a][i] != par[b][i]) {
                a = par[a][i], b = par[b][i];
            }
        }
        return par[a][0];
    };
    vector<int> dp(n + 1);
    for (int i = 1; i <= q; i++) {
        int a, b; cin >> a >> b;
        dp[a]++; dp[b]++;
        dp[par[lca(a, b)][0]]--;    // lca 算到兩次
        dp[lca(a, b)]--;    // lca 的父節點算 0 次
    }
    auto ans_dfs = [&](auto self, int u, int pre) -> void {
        for (auto v : tree[u]) {
            if (v == pre) continue;
            self(self, v, u);
            dp[u] += dp[v];
        }
    };
    ans_dfs(ans_dfs, 1, 0);
    for (int i = 1; i <= n; i++) {
        cout << dp[i] << " ";
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