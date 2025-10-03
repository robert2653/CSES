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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    map<int, vector<tuple<int, int, int>>> e;
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        e[w].emplace_back(u, v, i);
    }
    DSU dsu(n);
    vector<int> ans(m);
    for (auto [w, v] : e) {
        for (auto [u, v, id] : v) {
            if (!dsu.same(u, v)) {
                ans[id] = 1;
            }
        }
        for (auto [u, v, id] : v) {
            dsu.merge(u, v);
        }
    }
    for (int i = 0; i < m; i++) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }
    return 0;
}