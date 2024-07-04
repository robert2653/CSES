#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr int N = 5e4;

struct SCC {
    int n, cur, cnt;
    vector<vector<int>> adj;
    vector<int> stk, dfn, low, bel;
    SCC(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
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
    int n, m, q;
    cin >> n >> m >> q;
    SCC g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    g.work();
    auto f = g.compress();


    vector adj(f.n, vector<int>());
    vector rev(f.n, vector<int>());
    vector<int> in(f.n);
    vector<bitset<N>> dp(f.n);

    for (auto [i, j] : f.edges) {
        adj[i].push_back(j);
        rev[j].push_back(i);
        in[j]++;
    }

    vector<int> order;
    order.reserve(f.n);
    queue<int> topo;
    for (int i = 0; i < f.n; i++) {
        if (in[i] == 0) {
            topo.push(i);
        }
    }
    while (!topo.empty()) {
        int u = topo.front();
        topo.pop();
        order.push_back(u);
        for (auto v : adj[u]) {
            in[v]--;
            if (in[v] == 0) {
                topo.push(v);
            }
        }
    }

    reverse(order.begin(), order.end());
    for (auto u : order) {
        dp[u].set(u);
        for (auto v : rev[u]) {
            dp[v] |= dp[u];
        }
    }

    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (dp[g.bel[u]].test(g.bel[v])) cout << "YES\n";
        else cout << "NO\n";
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