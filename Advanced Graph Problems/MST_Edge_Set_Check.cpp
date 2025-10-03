#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct DSU {
    int n;
    vector<int> f, siz, stk;
    DSU(int n) : n(n), f(n), siz(n, 1) {
        iota(f.begin(), f.end(), 0);
        stk.clear();
    }
    int find(int x) {
        return x == f[x] ? x : find(f[x]);
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
        stk.push_back(y);
        return true;
    }
    void undo(int x) {
        while (stk.size() > x) {
            int y = stk.back();
            stk.pop_back();
            n++;
            siz[f[y]] -= siz[y];
            f[y] = y;
        }
    }
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    map<int, vector<tuple<int, int, int>>> e;
    vector<array<int, 3>> edges(m);
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--;
        v--;
        edges[i] = {u, v, w};
        e[w].emplace_back(u, v, i);
    }
    map<int, map<int, vector<int>>> vis; // w to [qry id] to [edge id]
    for (int i = 0; i < q; i++) {
        int sz;
        cin >> sz;
        for (int j = 0; j < sz; j++) {
            int id;
            cin >> id;
            id--;
            int w = edges[id][2];
            vis[w][i].push_back(id);
        }
    }
    DSU dsu(n);
    vector<int> ans(q, 1);
    for (auto [w, v] : e) {
        for (auto it = vis[w].begin(); it != vis[w].end();) {
            auto [qid, edgeIds] = *it;
            int sz = dsu.stk.size();
            for (auto id : edgeIds) {
                auto [u, v, _] = edges[id];
                if (dsu.same(u, v)) {
                    ans[qid] = 0;
                    break;
                } else {
                    dsu.merge(u, v);
                }
            }
            dsu.undo(sz);
            if (ans[qid] == 0) {
                it = vis[w].erase(it);
            } else {
                it++;
            }
        }
        for (auto [u, v, id] : v) {
            dsu.merge(u, v);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << (ans[i] ? "YES\n" : "NO\n");
    }
    return 0;
}