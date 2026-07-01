#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using ll = long long;

struct HLD {
    int n, cur;
    vector<int> siz, top, dep, par, in, out, seq;
    vector<vector<int>> adj;
    HLD(int n) : n(n), cur(0) {
        siz.resize(n); top.resize(n); dep.resize(n);
        par.resize(n); in.resize(n); out.resize(n);
        seq.resize(n); adj.assign(n, {});
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void work(int rt = 0) {
        top[rt] = rt;
        dep[rt] = 0;
        par[rt] = -1;
        dfs1(rt); dfs2(rt);
    }
    void dfs1(int u) {
        if (par[u] != -1) adj[u].erase(find(adj[u].begin(), adj[u].end(), par[u]));
        siz[u] = 1;
        for (auto &v : adj[u]) {
            par[v] = u, dep[v] = dep[u] + 1;
            dfs1(v);
            siz[u] += siz[v];
            if (siz[v] > siz[adj[u][0]]) {
                swap(v, adj[u][0]);
            } // 讓 adj[u][0] 是重子節點
        }
    }
    void dfs2(int u) {
        in[u] = cur++;
        seq[in[u]] = u; // dfn 對應的編號
        for (auto v : adj[u]) {
            top[v] = v == adj[u][0] ? top[u] : v;
            dfs2(v);
        }
        out[u] = cur;
    }
    int lca(int u, int v) {
        while (top[u] != top[v]) {
            if (dep[top[u]] > dep[top[v]]) {
                u = par[top[u]];
            } else {
                v = par[top[v]];
            }
        }
        return dep[u] < dep[v] ? u : v;
    }
    int dist(int u, int v) {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }
    int jump(int u, int k) {
        if (dep[u] < k) return -1;
        int d = dep[u] - k;
        while (dep[top[u]] > d) u = par[top[u]];
        return seq[in[u] - dep[u] + d];
    }
    bool isAncester(int u, int v) {
        return in[u] <= in[v] && in[v] < out[u];
    }
    int rootedParent(int rt, int v) {
        if (rt == v) return rt;
        if (!isAncester(v, rt)) return par[v];
        auto it = upper_bound(adj[v].begin(), adj[v].end(), rt,
            [&](int x, int y) {
                return in[x] < in[y];
            }) - 1;
        return *it;
    }
    int rootedSize(int rt, int v) {
        if (rt == v) return n;
        if (!isAncester(v, rt)) return siz[v];
        return n - siz[rootedParent(rt, v)];
    }
    int rootedLca(int rt, int a, int b) {
        return lca(rt, a) ^ lca(a, b) ^ lca(b, rt);
    }
};

// 隨編選一點當根，由深到淺選，用重心剖分維護
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    HLD hld(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
        hld.addEdge(u, v);
    }
    hld.work();

    vector<bool> vis(n);
    vector<int> siz(n), par(n, -1);
    auto findSize = [&](auto &&self, int u, int p) -> int {
        siz[u] = 1;
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            siz[u] += self(self, v, u);
        }
        return siz[u];
    };
    auto findCen = [&](auto &&self, int u, int p, int sz) -> int {
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            if (siz[v] * 2 > sz) return self(self, v, u, sz);
        }
        return u;
    };
    auto buildCen = [&](auto &&self, int u, int p) -> void {
        findSize(findSize, u, p);
        int c = findCen(findCen, u, -1, siz[u]);
        vis[c] = true, par[c] = p;
        for (int v : g[c]) if (!vis[v]) self(self, v, c);
    };
    buildCen(buildCen, 0, -1);

    vector<int> dep(n);
    auto getDep = [&](auto &&self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            dep[v] = dep[u] + 1;
            self(self, v, u);
        }
    };
    dep[0] = 0;
    getDep(getDep, 0, -1);

    vector<int> ord(n);
    iota(ord.begin(), ord.end(), 0);
    sort(ord.begin(), ord.end(), [&](int a, int b) {
        return dep[a] > dep[b];
    });

    vector<int> ans;
    vector<int> dp(n, n);   // 維護重心樹上每個點到最近辦公室的距離，初始為無限大
    auto update = [&](int u) {
        dp[u] = 0;
        for (int i = 0, v = par[u]; v != -1; i++, v = par[v]) {
            dp[v] = min(dp[v], hld.dist(u, v));
        }
    };
    auto query = [&](int u) -> int {
        int res = dp[u];
        for (int i = 0, v = par[u]; v != -1; i++, v = par[v]) {
            res = min(res, dp[v] + hld.dist(u, v));
        }
        return res;
    };

    for (auto u : ord) {
        if (query(u) >= k) {
            ans.push_back(u);
            update(u);
        }
    }

    cout << ans.size() << "\n";
    for (auto x : ans) {
        cout << x + 1 << " \n"[x == ans.back()];
    }

    return 0;
}