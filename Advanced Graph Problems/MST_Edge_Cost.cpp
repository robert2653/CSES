#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int Lg = 20; // __lg(max(n, qi)), [0, Lg]
vector<vector<int>> up, mxedge;
vector<int> dep, dfn;
void build(int n, vector<vector<pair<int, int>>> &g, int rt = 0) {
    up.assign(n, vector<int>(Lg + 1));
    mxedge.assign(n, vector<int>(Lg + 1));
    dep.assign(n, 0); dfn.assign(n, 0);
    int cur = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        for (int i = 1; i <= Lg; i++) {
            int nxt = up[x][i - 1];
            up[x][i] = up[nxt][i - 1];
            mxedge[x][i] = max(mxedge[x][i - 1], mxedge[nxt][i - 1]);
        }
        for (auto [y, w] : g[x]) {
            if (y == p) continue;
            up[y][0] = x;
            mxedge[y][0] = w;
            dep[y] = dep[x] + 1;
            self(self, y, x);
        }
    };
    dfs(dfs, rt, rt);
}
int lca(int a, int b) {
    if (dep[a] < dep[b]) swap(a, b);
    int pull = dep[a] - dep[b];
    for (int i = 0; i <= Lg; i++)
        if (pull & (1 << i)) a = up[a][i];
    if (a == b) return a;
    for (int i = Lg; i >= 0; i--)
        if (up[a][i] != up[b][i])
            a = up[a][i], b = up[b][i];
    return up[a][0];
}
int jump(int x, int k) {
    int mxe = 0;
    for (int i = Lg; i >= 0; i--)
        if (k >> i & 1) {
            mxe = max(mxe, mxedge[x][i]);
            x = up[x][i];
        }
    return mxe;
}

struct DSU {
    int n;
    vector<int> f, siz;
    DSU(int n) : n(n), f(n), siz(n, 1) {
        iota(f.begin(), f.end(), 0);
    }
    int find(int x) {
        if (f[x] == x) return x;
        return f[x] = find(f[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        f[y] = x;
        n--;
        return true;
    }
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<array<int, 4>> edges(m);
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges[i] = {w, u, v, i};
    }
    sort(edges.begin(), edges.end());
    vector<int> used(m);
    vector<ll> ans(m);
    ll sum = 0;
    vector<vector<pair<int, int>>> g(n);
    for (int i = 0; i < m; i++) {
        auto [w, u, v, id] = edges[i];
        if (!dsu.same(u, v)) {
            dsu.merge(u, v);
            g[u].emplace_back(v, w);
            g[v].emplace_back(u, w);
            used[i] = 1;
            sum += w;
        }
    }
    build(n, g);
    for (int i = 0; i < m; i++) {
        auto [w, u, v, id] = edges[i];
        if (used[i]) {
            ans[id] = sum;
            continue;
        } else {
            int l = lca(u, v);
            int mxe = max(jump(u, dep[u] - dep[l]), jump(v, dep[v] - dep[l]));
            ans[id] = sum - mxe + w;
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}