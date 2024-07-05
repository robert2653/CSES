#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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
    int n, m;
    cin >> n >> m;
    SCC g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    g.work();
    SCC::Graph f = g.compress();
    if (f.n == 1) {
        cout << 0 << "\n";
        return;
    }

    vector adj(f.n, vector<int>()), rev_adj(f.n, vector<int>());
    vector<int> in(f.n), out(f.n), vis(f.n), rev_vis(f.n);
    for (auto e : f.edges) {
        in[e.second]++;
        out[e.first]++;
        adj[e.first].push_back(e.second);
        rev_adj[e.second].push_back(e.first);
    }
    vector<int> S, T;
    for (int i = 0; i < f.n; i++) {
        if (in[i] == 0) S.push_back(i);
        if (out[i] == 0) T.push_back(i);
    }
    vector<int> inmat(f.n);

    auto dfs = [&](auto &&self, int u) -> int {
        if (vis[u]) return -1;
        vis[u] = 1;
        int ret = -1;
        if (out[u] == 0) ret = u;
        for (int v : adj[u]) {
            int t = self(self, v);
            if (t != -1) ret = t;
        }
        return ret;
    };

    vector<pair<int, int>> mat;
    for (int u : S) {
        int v = dfs(dfs, u);
        if (v != -1) {
            mat.emplace_back(u, v);
            inmat[u] = inmat[v] = 1;
        }
    }

    vector<pair<int, int>> ans;
    if (mat.size() == 1 && S.size() == 2) {
        // Edge case, change
        // 現在選的另一個 S 到不了，要換
        auto it = S.begin(); // 另一個 S
        while (*it == mat[0].first) it++;
        auto check = [&]() -> bool {
            vector<bool> vis(f.n);
            vis[*it] = true;
            queue<int> q;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                for (int v : adj[u]) {
                    if (vis[v]) continue;
                    vis[v] = 1;
                    q.push(v);
                }
            }
            return vis[mat[0].second];
        };
        if (!check()) {
            inmat[mat[0].first] = 0;
            inmat[*it] = 1;
            mat[0].first = *it;
        }
    }
    for (int i = 0; i < mat.size(); i++) {
        ans.emplace_back(mat[i].second, mat[(i + 1) % mat.size()].first);
    }

    auto pS = S.begin(), pT = T.begin();
    while (true) {
        while (pS != S.end() && inmat[*pS]) pS++;
        while (pT != T.end() && inmat[*pT]) pT++;
        if (pS == S.end() && pT == T.end()) break;
        int u = (pS == S.end() ? *S.begin() : *pS);
        int v = (pT == T.end() ? *T.begin() : *pT);
        inmat[u] = inmat[v] = 1;
        ans.emplace_back(v, u);
    }

    vector<int> delegate(f.n, -1);
    for (int i = 0; i < n; i++) {
        if (delegate[g.bel[i]] == -1) {
            delegate[g.bel[i]] = i;
        }
    }

    cout << ans.size() << "\n";
    for (auto [u, v] : ans) cout << delegate[u] + 1 << " " << delegate[v] + 1 << "\n";
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