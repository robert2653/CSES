#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SCC {
    int n, cur, cnt;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    SCC(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (auto y : adj[x]) {
            if (dfn[y] == -1) {
                dfs(y);
                low[x] = min(low[x], low[y]);
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
            if (dfn[i] == -1) dfs(i);
        }
        return bel;
    }
    struct Graph {
        int n;
        vector<pair<int, int>> edges;
        vector<int> siz;
        vector<int> cnte;
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (auto j : adj[i]) {
                if (bel[i] != bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                } else {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};

void solve() {
    int n, m; cin >> n >> m;
    SCC g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    g.work();
    if (g.cnt == 1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
        for (int i = 0; i < n; i++) {
            // cerr << i << " " << g.bel[i] << "\n";
        }
        cerr << "\n";
        auto f = g.compress();
        vector<set<int>> adj(f.n);
        for (auto [i, j] : f.edges) {
            adj[i].insert(j);
            // cerr << i << " " << j << "\n";
        }
        cerr << "\n";
        for (int i = 0; i < f.n; i++) {
            if (adj[i].size() != f.n - 1) {
                // cerr << i << " " << adj[i].size() << "\n";
                int p = i == 0 ? 1 : 0;
                for (auto j : adj[i]) {
                    if (p == j) p++;
                }
                for (int j = 0; j < n; j++) {
                    if (g.bel[j] == i) {
                        cout << j + 1 << " ";
                        break;
                    }
                }
                for (int j = 0; j < n; j++) {
                    if (g.bel[j] == p) {
                       cout << j + 1 << "\n";
                       break;
                    }
                }
                return;
            }
        }
    }
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