#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;

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

const int N = 2E5;
const int Lg = __lg(N); // __lg(max(n, qi)), [0, Lg]
int up[N][Lg + 1];
int pmx[N][Lg + 1];
vector<int> dep, dfn;
void build(int n, vector<vector<pair<int, int>>> &g, int rt = 0) {
    int cur = 0;
    auto dfs = [&](auto self, int x, int p, int w) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        pmx[x][0] = w;
        for (int i = 1; i <= Lg; i++) {
            int nxt = up[x][i - 1];
            up[x][i] = up[nxt][i - 1];
            pmx[x][i] = max(pmx[x][i - 1], pmx[nxt][i - 1]);
        }
        for (auto [y, w] : g[x]) {
            if (y == p) continue;
            up[y][0] = x;
            dep[y] = dep[x] + 1;
            self(self, y, x, w);
        }
    };
    dfs(dfs, rt, rt, 0);
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
    for (int i = Lg; i >= 0; i--)
        if (k >> i & 1) {
            x = up[x][i];
        }
    return x;
}
int qry(int x, int k) {
    int ans = 0;
    for (int i = Lg; i >= 0; i--)
        if (k >> i & 1) {
            ans = max(ans, pmx[x][i]);
            x = up[x][i];
        }
    return ans;
}
 
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
 
    DSU dsu(n);
    dep.assign(n, 0); dfn.assign(n, 0);
    vector<vector<pair<int, int>>> g(n);
    for (int i = 1; i <= m; i++) {
        int u, v; 
        cin >> u >> v;
        u--; v--;
        if (!dsu.same(u, v)) {
            dsu.merge(u, v);
            g[u].emplace_back(v, i);
            g[v].emplace_back(u, i);
        }
    }
    vector<int> rt(n, -1);
    auto dfs = [&](auto self, int u, int r) -> void {
        rt[u] = r;
        for (auto [v, w] : g[u]) {
            if (rt[v] == -1) {
                self(self, v, r);
            }
        }
    };
    for (int i = 0; i < n; i++) {
        if (rt[i] == -1) {
            dfs(dfs, i, i);
            build(n, g, i);
        }
    }
 
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (!dsu.same(u, v)) {
            cout << -1 << "\n";
        } else {
            int l = lca(u, v);
            int ans = max(qry(u, dep[u] - dep[l]), qry(v, dep[v] - dep[l]));
            cout << ans << "\n";
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
    return 0;
}