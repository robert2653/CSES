#include <bits/stdc++.h>
using namespace std;

const int Q = 20; // log(q) or log(n)
vector<vector<int>> up;
vector<int> dep, dfn;
void build(int n, vector<vector<int>> &g, int rt = 0) {
    up.assign(n, vector<int>(Q + 1));
    dep.assign(n, 0);
    dfn.assign(n, 0);
    int cur = 0;
    auto dfs = [&](auto self, int x, int p) -> void {
        dfn[x] = cur++;
        up[x][0] = p;
        for (int i = 1; i <= Q; i++)
            up[x][i] = up[up[x][i - 1]][i - 1];
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
    for (int i = 0; i <= Q; i++)
        if (pull & (1 << i))
            a = up[a][i];
    if (a == b) return a;
    for (int i = Q; i >= 0; i--)
        if (up[a][i] != up[b][i])
            a = up[a][i], b = up[b][i];
    return up[a][0];
}
int jump(int x, int k) {
    for (int i = Q; i >= 0; i--)
        if (k >> i & 1)
            x = up[x][i];
    return x;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        p--;
        g[p].push_back(i);
    }
    build(n, g);
    while (q--) {
        int x, y, k;
        cin >> x >> k;
        x--;
        y = jump(x, k - 1);
        x = jump(x, k);
        if (x == y) {
            cout << -1 << "\n";
        } else {
            cout << x + 1 << "\n";
        }
    }
    return 0;
}