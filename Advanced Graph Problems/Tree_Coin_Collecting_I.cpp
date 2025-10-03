#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int Lg = 20; // __lg(max(n, qi)), [0, Lg]
vector<vector<int>> up, min_mind;
vector<int> dep, dfn, coin, pref, mind;
void build(int n, vector<vector<int>> &g, int rt = 0) {
    up.assign(n, vector<int>(Lg + 1));
    min_mind.assign(n, vector<int>(Lg + 1, 1E9));
    dep.assign(n, 0); dfn.assign(n, 0);
    pref.assign(n, 0);
    int cur = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        min_mind[x][0] = min(min_mind[x][0], mind[p]);
        pref[x] = pref[p] + coin[x];
        for (int i = 1; i <= Lg; i++) {
            up[x][i] = up[up[x][i - 1]][i - 1];
            min_mind[x][i] = min(min_mind[x][i - 1], min_mind[up[x][i - 1]][i - 1]);
        }
        for (auto y : g[x]) {
            if (y == p) continue;
            up[y][0] = x;
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
int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}
int jump(int x, int k) {
    int res = mind[x];
    if (k == 0) return res;
    for (int i = Lg; i >= 0; i--)
        if (k >> i & 1) {
            res = min(res, min_mind[x][i]);
            x = up[x][i];
        }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    coin.assign(n, 0);
    mind.assign(n, 1E9);
    for (int i = 0; i < n; i++) {
        cin >> coin[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dfs1 = [&](auto self, int x, int p) -> void {
        if (coin[x]) {
            mind[x] = 0;
        }
        for (auto y : g[x]) {
            if (y == p) continue;
            self(self, y, x);
            mind[x] = min(mind[x], mind[y] + 1);
        }
    };
    auto dfs2 = [&](auto self, int x, int p) -> void {
        for (auto y : g[x]) {
            if (y == p) continue;
            mind[y] = min(mind[x] + 1, mind[y]);
            self(self, y, x);
        }
    };
    dfs1(dfs1, 0, 0);
    dfs2(dfs2, 0, 0);
    build(n, g);
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        if (pref[u] + pref[v] - 2 * pref[l] + coin[l] > 0) {
            cout << dist(u, v) << "\n";
        } else {
            int d1 = dep[u] - dep[l];
            int d2 = dep[v] - dep[l];
            cout << dist(u, v) + min(jump(u, d1), jump(v, d2)) * 2 << "\n";
        }
    }
    return 0;
}