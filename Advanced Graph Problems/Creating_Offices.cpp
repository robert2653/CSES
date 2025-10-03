#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using ll = long long;

const int N = 2E5;
const int Lg = __lg(N); // __lg(max(n, qi)), [0, Lg]
int up[N][Lg + 1];
vector<int> dep, dfn;
void build(int n, vector<vector<int>> &g, int rt = 0) {
    dep.assign(n, 0); dfn.assign(n, 0);
    int cur = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        for (int i = 1; i <= Lg; i++) {
            int nxt = up[x][i - 1];
            up[x][i] = up[nxt][i - 1];
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
int jump(int x, int k) {
    for (int i = Lg; i >= 0; i--)
        if (k >> i & 1) {
            x = up[x][i];
        }
    return x;
}
int dist(int a, int b) {
    return dep[a] + dep[b] - 2 * dep[lca(a, b)];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // freopen("test_input.txt", "r", stdin);

    int n, k;
    cin >> n >> k;
    vector<vector<int>> g(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    vector<bool> vis(n);
    vector<int> siz(n), par(n, -1);
    auto findSize = [&](auto self, int u, int p) -> int {
        siz[u] = 1;
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            siz[u] += self(self, v, u);
        }
        return siz[u];
    };
    auto findCen = [&](auto self, int u, int p, int sz) -> int {
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            if (siz[v] * 2 > sz) return self(self, v, u, sz);
        }
        return u;
    };
    auto buildCen = [&](auto self, int u, int p) -> void {
        findSize(findSize, u, p);
        int c = findCen(findCen, u, -1, siz[u]);
        vis[c] = true, par[c] = p;
        for (int v : g[c]) if (!vis[v]) self(self, v, c);
    };
    auto start = chrono::high_resolution_clock::now();
    buildCen(buildCen, 0, -1);
    auto end = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(end - start);
    cerr << "建構時間: " << duration.count() << " ms\n";

    vector<int> dep(n);
    auto getDep = [&](auto self, int u, int p) -> void {
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

    build(n, g, 0);
    vector<int> ans;
    vector<int> dp(n, n);
    auto update = [&](int u) {
        dp[u] = 0;
        for (int i = 0, v = par[u]; v != -1; i++, v = par[v]) {
            dp[v] = min(dp[v], dist(u, v));
        }
    };
    auto query = [&](int u) -> int {
        int res = dp[u];
        for (int i = 0, v = par[u]; v != -1; i++, v = par[v]) {
            res = min(res, dp[v] + dist(u, v));
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
    auto end2 = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(end2 - end);
    cerr << "查詢時間: " << duration.count() << " ms\n";

    return 0;
}