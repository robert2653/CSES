#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct EBCC { // CF/contest/1986/pF
    int n, cur, cnt;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    vector<pair<int, int>> bridges; // 關鍵邊
    EBCC(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        bridges.clear();
        cur = cnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (auto y : adj[x]) {
            if (y == p) continue;
            if (dfn[y] == -1) {
                dfs(y, x);
                low[x] = min(low[x], low[y]);
                if (low[y] > dfn[x]) {
                    bridges.emplace_back(x, y);
                }
            } else if (bel[y] == -1) {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    vector<int> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        return bel;
    }
    
    struct Graph {
        int n;
        vector<pair<int, int>> edges;
        vector<int> siz; // BCC 內節點數
        vector<int> cnte; // BCC 內邊數
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (auto j : adj[i]) {
                if (bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                } else if (i < j) {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};

void solve() {
    int n, m;
    cin >> n >> m;
    EBCC g(n);
    vector<vector<pair<int, int>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
        adj[u].emplace_back(v, i);
        adj[v].emplace_back(u, i);
    }
    g.work();
    EBCC::Graph f = g.compress();
    if (f.n > 1) {
        cout << "IMPOSSIBLE\n";
        return;
    }
    vector<int> vis(n);
    vector<int> in_ans(m);
    vector<pair<int, int>> ans;
    auto dfs = [&](auto &&self, int u) -> void {
        vis[u] = 1;
        for (auto [v, id] : adj[u]) {
            if (!in_ans[id]) {
                ans.emplace_back(u, v);
                in_ans[id] = 1;
            }
            if (!vis[v]) {
                self(self, v);
            }
        }
    };
    dfs(dfs, 0);
    for (auto [u, v] : ans) cout << u + 1 << " " << v + 1 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}