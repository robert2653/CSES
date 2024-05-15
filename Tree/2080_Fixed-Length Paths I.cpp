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
    int n, k; cin >> n >> k;
    vector<vector<int>> tree(n + 1);
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<map<int, int>> vmp(n + 1);
    vector<int> lazy(n + 1);    // swap 後標記 +1
    int ans = 0;
    auto dfs = [&](auto self, int u, int pre) -> void {
        vmp[u][0] = 1;
        for (auto v : tree[u]) {
            if (v == pre) continue;
            self(self, v, u);
            int swapped = 0;
            if (vmp[v].size() > vmp[u].size()) {
                swap(vmp[v], vmp[u]);
                swap(lazy[u], lazy[v]);
                lazy[u]++;
                swapped = 1;
            }
            for (auto [i, j] : vmp[v]) {
                if (vmp[u].count(k - !swapped - i - lazy[u] - lazy[v])) {
                    ans += j * vmp[u][k - !swapped - i - lazy[u] - lazy[v]];
                }
            }
            for (auto [i, j] : vmp[v]) {
                vmp[u][i + !swapped - lazy[u] + lazy[v]] += j;
            }
            vmp[v].clear();
        }
    };
    dfs(dfs, 1, 0);
    cout << ans << "\n";
}
signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}