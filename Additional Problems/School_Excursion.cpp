#include <bits/stdc++.h>
#pragma GCC target("popcnt")

using namespace std;
using ll = long long;

const int N = 1E5;

struct DSU {
    int n;
    vector<int> boss, siz;
    DSU(int n = 0) : n(n) {
        init(n);
    }
    void init(int n) {
        boss.resize(n);
        iota(boss.begin(), boss.end(), 0);
        siz.resize(n, 1);
    }
    int find(int x) {
        if (boss[x] == x) return x;
        return boss[x] = find(boss[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    void merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return;
        n--;
        if (siz[x] < siz[y]) swap(x, y);
        boss[y] = x;
        siz[x] += siz[y];
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
    DSU dsu(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--;
        v--;
        dsu.merge(u, v);
    }
    bitset<N + 1> bs;
    bs[0] = 1;
    
    vector<int> vis(n);
    for (int i = 0; i < n; i++) {
        int id = dsu.find(i);
        if (!vis[id]) {
            vis[id] = 1;
            bs |= bs << dsu.size(i);
        }
    }
    for (int i = 0; i < n; i++) {
        cout << bs[i + 1];
    }

    return 0;
}