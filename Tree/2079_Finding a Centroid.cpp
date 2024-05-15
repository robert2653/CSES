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

void solve(){
    int n; cin >> n;
    vector<vector<int>> adj(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int ans = 0;
    auto dfs = [&](auto self, int u, int pre) -> int {
        int subsz_sum = 0;  // u 以下的 size
        bool u_is_centroid = 1;
        for (int v : adj[u]) {
            if (v == pre) continue;
            int subsz = self(self, v, u);
            if (subsz > n / 2) {
                u_is_centroid = 0;
            }
            subsz_sum += subsz;
        }
        if (n - 1 - subsz_sum > n / 2) {    // u 以上的 size
            u_is_centroid = 0;
        }
        if (u_is_centroid) {
            ans = u;
        }
        return subsz_sum + 1;
    };
    dfs(dfs, 1, 0);
    cout << ans << "\n";
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