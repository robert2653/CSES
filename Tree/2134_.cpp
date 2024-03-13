#include <bits/stdc++.h>
#pragma GCC optimize ("O3")
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;

template <class Node>
struct Seg {
    int n;
    vector<Node> tree;
    Seg (vector<Node> init_){
        n = init_.size() - 1;
        tree.resize(4 * n);
        function <void(int, int, int)> build = [&](int now, int l, int r) {
            if (l == r) {
                tree[now] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(now << 1, l, m);
            build((now << 1) + 1, m + 1, r);
            pull(now);
        };
        build(1, 1, n);
    }
    Node query(int l, int r, int ql, int qr, int now){
        int m = (l + r) >> 1;
        if(qr < l || ql > r){
            return Node();
        }
        if(ql <= l && r <= qr){
            return tree[now];
        }
	    return query(l, m, ql, qr, now << 1) + query(m + 1, r, ql, qr, (now << 1) + 1);
    }
    Node query(int l, int r) { return query(1, n, l, r, 1); }
    void pull(int now){
        tree[now] = tree[now << 1] + tree[(now << 1) + 1];
    }
    void modify(int l, int r, int idx, int now, int add){
        if(l == r){
// ------------------------------how to modify ?-----------------------------------
            tree[now].mx = add;
// --------------------------------------------------------------------------------
            return;
        }
        int m = (l + r) >> 1;
        if(idx <= m){
            modify(l, m, idx, now << 1, add);
        }
        else {
            modify(m + 1, r, idx, (now << 1) + 1, add);
        }
        pull(now);
    }
    void modify(int idx, int add) { modify(1, n, idx, 1, add); }
};
// ------------------------define structure and info plus------------------------
struct Node {
    int mx;
    Node() {
        mx = 0;
    }
};
Node operator + (const Node &a, const Node &b) {
    Node c;
    c.mx = max(a.mx, b.mx);
    return c;
}

void solve(){
    int n, q; cin >> n >> q;
    clock_t now = clock();
    vector<vector<int>> tree(n + 1, vector<int>());
    cerr << ((double)(clock() - now)) / CLOCKS_PER_SEC << "\n";
    vector<int> depth(n + 1), sz(n + 1), par(n + 1), heavy_son(n + 1), node_val(n + 1);
    for (int i = 1; i <= n; i++) cin >> node_val[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    cerr << ((double)(clock() - now)) / CLOCKS_PER_SEC << "\n";
    auto dfs = [&](auto self, int u, int pre) -> void {
        sz[u] = 1;
        par[u] = pre;
        heavy_son[u] = -1;
        for (int v : tree[u]) {
            if (v == pre) continue;
            depth[v] = depth[u] + 1;
            self(self, v, u);
            sz[u] += sz[v];
            if (heavy_son[u] == -1 || sz[v] > sz[heavy_son[u]]) heavy_son[u] = v;
        }
    };
    dfs(dfs, 1, 0);
    cerr << ((double)(clock() - now)) / CLOCKS_PER_SEC << "\n";
    vector<int> top(n + 1), dfn(n + 1); // 鏈頭
    vector<Node> init(n + 1, Node());
    int order = 0;
    auto link = [&](auto self, int u, int head) -> void {
        top[u] = head;
        dfn[u] = ++order;
        init[order].mx = node_val[u];
        if (heavy_son[u] != -1) self(self, heavy_son[u], head);   // 當前鏈
        for (int v : tree[u]) {
            if (v == par[u] || v == heavy_son[u]) continue;
            // 進新鏈
            self(self, v, v);
        }
    };
    link(link, 1, 1);
    Seg<Node> seg(init);
    auto query = [&](int a, int b) -> int {
        int ans = 0;
        while (top[a] != top[b]) {
            if (depth[top[a]] < depth[top[b]]) swap(a, b);  // a 的 head 比較高
            ans = max(ans, seg.query(dfn[top[a]], dfn[a]).mx);
            a = par[top[a]];    // 跳鏈
        }
        if (dfn[a] > dfn[b]) swap(a, b);    // a 比 b 低要換，用 depth 也行
        ans = max(ans, seg.query(dfn[a], dfn[b]).mx);
        return ans;
    };
    for (int i = 1; i <= q; i++) {
        int op; cin >> op;
        if (op == 1) {
            int s, x; cin >> s >> x;
            seg.modify(dfn[s], x);
        }
        else {
            int a, b; cin >> a >> b;
            cout << query(a, b) << "\n";
        }
    }
}
signed main(){
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt", "w", stdout);
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}