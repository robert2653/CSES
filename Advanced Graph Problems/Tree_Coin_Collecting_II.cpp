#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int Lg = 20; // __lg(max(n, qi)), [0, Lg]
vector<vector<int>> up;
vector<vector<ll>> pref;
vector<int> dep, dfn, coin, cnt;
void build(int n, vector<vector<int>> &g, int rt = 0) {
    up.assign(n, vector<int>(Lg + 1));
    pref.assign(n, vector<ll>(Lg + 1, 1E9));
    dep.assign(n, 0); dfn.assign(n, 0);
    int cur = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        pref[x][0] = cnt[p];
        for (int i = 1; i <= Lg; i++) {
            up[x][i] = up[up[x][i - 1]][i - 1];
            pref[x][i] = pref[x][i - 1] + pref[up[x][i - 1]][i - 1];
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n);
    vector<ll> sum(n);
    coin.assign(n, 0);
    cnt.assign(n, 0);
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
    auto dfs = [&](auto self, int x, int p) -> void {
        if (coin[x]) {
            cnt[x] = 1;
        }
        for (auto y : g[x]) {
            if (y == p) continue;
            self(self, y, x);
            cnt[x] += cnt[y];
            sum[x] += sum[y] + cnt[y];
        }
    };
    dfs(dfs, 0, 0);
    build(n, g);
    while (q--) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        int l = lca(u, v);
        if (l == u || l == v) {
            if (l == u) {
                swap(u, v);
            }
        }
        int d1 = dep[u] - dep[l];
        int d2 = dep[v] - dep[l];
        auto jump = [&](int x, int k) -> ll {
            int res = cnt[x];
            if (k < 0) return 0;
            if (k == 0) return res;
            for (int i = Lg; i >= 0; i--)
            if (k >> i & 1) {
                res += pref[x][i];
                x = up[x][i];
            }
            return res;
        };
        ll ans = sum[l] * 2;
        ll temp = jump(u, d1 - 1);
        ans -= temp;
        temp = jump(v, d2 - 1);
        ans -= temp;
        cout << ans << "\n";
    }
    return 0;
}