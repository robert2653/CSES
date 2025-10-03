#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SCC {
    int n, cur, cnt;
    vector<int> low, bel, dfn, stk;
    vector<vector<int>> g;
    SCC(int n) : n(n), cur(0), cnt(0), low(n), bel(n, -1), dfn(n, -1), g(n) {}
    void addEdge(int x, int y) {
        g[x].push_back(y);
    }
    void dfs(int x) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        for (int y : g[x]) {
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
                stk.pop_back();
                bel[y] = cnt;
            } while (x != y);
            cnt++;
        }
    }
    void work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) dfs(i);
        }
    }
    struct Graph {
        int n;
        vector<pair<int, int>> e;
        vector<int> siz, cnte;
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (int j : this->g[i]) {
                if (bel[i] != bel[j]) {
                    g.e.emplace_back(bel[i], bel[j]);
                } else {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};

void solve() {
    string s;
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
        for (auto [i, j] : f.e) {
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