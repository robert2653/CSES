// 數壓平裸題
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
struct edge {
    int from; int to;
    int weight;
};
struct node {
    int sum;
};
const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

struct BIT {    // BIT 都是 1-based 的查詢
    int n;
    vector<int> bit;
    BIT(int n) {    // 有幾個數
        this->n = n;
        bit.resize(n + 1, 0);
    }
    BIT(vector<int> &init) {    // 必須是 1-based
        this->n = init.size() - 1;
        bit.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            modify(i, init[i]);
        }
    }
    void modify(int i, int val) {
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    int query(int r) {
	    int ans = 0;
	    for (; r; r -= r & -r) ans += bit[r];
	    return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};

void solve(){
    int n, q; cin >> n >> q;
    vector<int> node_value(n + 1), euler_ordered_value(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> node_value[i];
    }
    vector<vector<int>> tree(n + 1, vector<int>());
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    vector<pii> tree_mapping(n + 1);
    int cnt = 0;
    auto dfs = [&](auto self, int u, int par) -> void {
        euler_ordered_value[++cnt] = node_value[u];
        tree_mapping[u].first = cnt;
        for (auto v : tree[u]) {
            if (v == par) continue;
            self(self, v, u);
        }
        tree_mapping[u].second = cnt;
    };
    dfs(dfs, 1, 0);
    BIT bit(euler_ordered_value);
    for (int i = 0; i < q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int s, x; cin >> s >> x;
            int now = bit.query(tree_mapping[s].first, tree_mapping[s].first);
            bit.modify(tree_mapping[s].first, x - now);
            // cout << "now = " << now << " x = " << x << endl;
        }
        else {
            int node; cin >> node;
            // cout << "node = " << node << " l = " << bit.query(tree_mapping[node].first - 1) << " r = " << bit.query(tree_mapping[node].second) << endl;
            cout << bit.query(tree_mapping[node].first, tree_mapping[node].second) << "\n";
        }
    }
}
signed main() {
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--) {
        solve();
    }
}