#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SCC {
    int n, cur, cnt;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    SCC(int n_ = 0) { init(n_); }
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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    SCC f(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        f.addEdge(u, v);
    }

    f.work();
    auto g = f.compress();
    int scc_n = g.n;
    vector<ll> b(scc_n);
    for (int i = 0; i < n; i++) {
        b[f.bel[i]] += a[i];
    }

    vector<vector<int>> ing(scc_n);
    for (auto [i, j] : g.edges) {
        ing[i].push_back(j);
    }

    vector<ll> dp(scc_n);
    vector<bool> vis(scc_n);
    auto dfs = [&](auto self, int x) -> ll {
        if (vis[x]) {
            return dp[x];
        }
        dp[x] = b[x];
        if (!ing[x].empty()) {
            ll res = 0;
            for (auto y : ing[x]) {
                res = max(res, self(self, y));
            }
            dp[x] += res;
        }
        vis[x] = true;
        return dp[x];
    };
    for (int i = 0; i < scc_n; i++) {
        dfs(dfs, i);
    }
    cout << *max_element(dp.begin(), dp.end()) << "\n";

    return 0;
}