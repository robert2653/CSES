#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct DSU {
    int n;
    vector<int> boss, siz, stk;
    DSU() {}
    DSU(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        boss.resize(n);
        iota(boss.begin(), boss.end(), 0);
        siz.assign(n, 1);
        stk.clear();
    }
    int find(int x) {
        return x == boss[x] ? x : find(boss[x]);
    }
    bool same(int x, int y) {
        return find(x) == find(y);
    }
    bool merge(int x, int y) {
        x = find(x); y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        boss[y] = x;
        n--;
        stk.push_back(y);
        return true;
    }
    void undo(int x) {
        while (stk.size() > x) {
            int y = stk.back();
            stk.pop_back();
            n++;
            siz[boss[y]] -= siz[y];
            boss[y] = y;
        }
    }
    int size(int x) {
        return siz[find(x)];
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;
    DSU dsu(n);

    map<pair<int, int>, int> mp;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);
        mp[{u, v}] = 0;
    }

    vector<int> ans(q + 1);

    vector<vector<pair<int, int>>> smt(4 << __lg(q));
    auto update = [&](auto &&self, int p, int l, int r, int ql, int qr, const pair<int, int> &v) -> void {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            smt[p].push_back(v);
            return;
        }
        int m = (l + r) / 2;
        self(self, p * 2, l, m, ql, qr, v);
        self(self, p * 2 + 1, m, r, ql, qr, v);
    };
    auto query = [&](auto &&self, int p, int l, int r) -> void {
        int cnt = dsu.stk.size();
        for (auto [u, v] : smt[p]) dsu.merge(u, v);
        if (r - l == 1) {
            ans[l] = dsu.n;
        } else {
            int m = (l + r) / 2;
            self(self, p * 2, l, m);
            self(self, p * 2 + 1, m, r);
        }
        dsu.undo(cnt);
    };

    for (int i = 1; i <= q; i++) {
        int op;
        cin >> op;

        int u, v;
        cin >> u >> v;
        u--, v--;
        if (u > v) swap(u, v);

        if (op == 1) {
            mp[{u, v}] = i;
        } else {
            update(update, 1, 0, q + 1, mp[{u, v}], i, {u, v});
            mp.erase({u, v});
        }
    }

    for (auto [e, i] : mp) {
        update(update, 1, 0, q + 1, i, q + 1, e);
    }
    query(query, 1, 0, q + 1);
    for (int i = 0; i <= q; i++) {
        cout << ans[i] << " \n"[i == q];
    }

    return 0;
}