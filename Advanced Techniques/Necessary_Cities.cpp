#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct VBCC {
    int n, cur, cnt;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    vector<bool> ap;
    VBCC(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        ap.assign(n, false);
        stk.clear();
        cur = cnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        int child = 0;
        for (int y : adj[x]) {
            if (y == p) continue;
            if (dfn[y] == -1) {
                dfs(y, x), child++;
                low[x] = min(low[x], low[y]);
                if (p != -1 && low[y] >= dfn[x]) {
                    ap[x] = true;
                }
            } else {
                low[x] = min(low[x], dfn[y]);
            }
        }
        if (p == -1 && child > 1) {
            ap[x] = true;
        }
        if (dfn[x] == low[x]) {
            // int y;
            // do {
            //     y = stk.back();
            //     bel[y] = cnt;
            //     stk.pop_back();
            // } while (y != x);
            int y = stk.back();
            while (y != x) {
                bel[y] = cnt;
                stk.pop_back();
                y = stk.back();
            }
            cnt++;
        }
    }
    vector<bool> work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i, -1);
            }
        }
        for (auto x : stk) {
            bel[x] = cnt++;
        }
        return ap;
    }
    struct Graph { // 不會有重邊
        int n;
        vector<pair<int, int>> edges;
        vector<int> siz; // BCC 內節點數
        vector<int> cnte; // BCC 內邊數
    };
    Graph compress() {
        Graph g;
        for (int i = 0; i < n; i++) {
            if (ap[i]) { // 如果是割點，將其自成一個連通分量
                bel[i] = cnt++;
            }
        }
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
    VBCC g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    g.work();

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (g.ap[i]) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}