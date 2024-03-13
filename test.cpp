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
    vector<int> depth(n + 1), sz(n + 1), heavy_son(n + 1), node_val(n + 1);
    vector<vector<int>> par(n + 1, vector<int>(18));
    for (int i = 1; i <= n; i++) cin >> node_val[i];
    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    auto dfs = [&](auto self, int u, int pre) -> void {
        sz[u] = 1;
        par[u][0] = pre;
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
    vector<int> top(n + 1), dfn(n + 1); // 鏈頭
    vector<Node> init(n + 1, Node());
    int order = 0;
    auto link = [&](auto self, int u, int head) -> void {
        top[u] = head;
        dfn[u] = ++order;
        init[order].mx = node_val[u];
        if (heavy_son[u] != -1) self(self, heavy_son[u], head);   // 當前鏈
        for (int v : tree[u]) {
            if (v == par[u][0] || v == heavy_son[u]) continue;
            // 進新鏈
            self(self, v, v);
        }
    };
    link(link, 1, 1);
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
    Seg<Node> seg(init);
    auto query = [&](int chi, int p) -> int {
        int ans = 0;
        while (chi != p) {
            if (top[chi] == chi) {
			    ans = max(ans, node_val[chi]);
			    chi = par[chi][0];
		    }
            else if (depth[top[chi]] > depth[p]) {
			    ans = max(ans, seg.query(dfn[top[chi]], dfn[chi]).mx);
			    chi = par[top[chi]][0];
		    }
            else {
			    ans = max(ans, seg.query(dfn[p], dfn[chi]).mx);
			    break;
		    }
        }
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
            int LCA = lca(a, b);
            cout << max({query(a, LCA), query(b, LCA), node_val[LCA]}) << "\n";
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