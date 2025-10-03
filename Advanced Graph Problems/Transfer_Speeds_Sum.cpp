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

    int n;
    cin >> n;
    vector<tuple<int, int, int>> e(n - 1);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        e.emplace_back(w, u, v);
    }
    sort(e.begin(), e.end(), greater());
    ll ans = 0;
    DSU dsu(n);
    for (auto [w, u, v] : e) {
        ans += 1LL * w * dsu.size(u) * dsu.size(v);
        dsu.merge(u, v);
    }
    cout << ans << "\n";
    return 0;
}