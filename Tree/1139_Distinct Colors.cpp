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
    vector<vector<int>> tree(n + 1);
    vector<int> node_val(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> node_val[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<int> ans(n + 1);
    auto dfs = [&](auto self, int u, int pre) -> set<int> {
        set<int> now = {node_val[u]};
        for (int v : tree[u]) {
            if (v == pre) continue;
            set<int> st = self(self, v, u);
            if (now.size() < st.size()) swap(now, st);
            now.insert(st.begin(), st.end());
        }
        ans[u] = now.size();
        return now;
    };
    dfs(dfs, 1, 0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
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