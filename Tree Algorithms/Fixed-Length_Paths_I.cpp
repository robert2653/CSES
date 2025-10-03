#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct CentroidDecomposition {
    int n, rt, k;
    vector<vector<int>> g, ctp;
    vector<bool> vis;
    vector<int> siz, par;
    vector<int> cnt;
    vector<vector<int>> dis; // 與第 i 個 cen 的距離 : disc[i][0] = dist(i, par[i])
    CentroidDecomposition(const vector<vector<int>> &g, int k) : n(g.size()), g(g), ctp(n), vis(n), siz(n), par(n), dis(n) {
        this->k = k;
        cnt.resize(k + 1);
        cnt[0] = 1;
        build(0, -1);
        for (auto &v : dis) reverse(v.begin(), v.end());
    }
    void findSize(int u, int p, int d) {
        mxd = max(mxd, d); // add
        siz[u] = 1;
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            findSize(v, u, d + 1);
            siz[u] += siz[v];
        }
    }
    int findCen(int u, int p, int sz) {
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            if (siz[v] * 2 > sz) return findCen(v, u, sz);
        }
        return u;
    }
    int mxd = 0;
    ll ans = 0;
    void getAns(int u, int p, int d, bool upd) {
        if (d > k) return;
        mxd = max(mxd, d);
        if (upd) cnt[d]++;
        else ans += cnt[k - d];
        for (int v : g[u]) {
            if (v == p || vis[v]) continue;
            getAns(v, u, d + 1, upd);
        }
    }
    void build(int u, int p, int f = 1) {
        mxd = 0;
        findSize(u, p, 0);
        int c = findCen(u, -1, siz[u]);
        if (!f) ctp[p].push_back(c);
        vis[c] = true, par[c] = p;
        if (mxd * 2 < k) return;

        mxd = 0;
        for (int v : g[c]) if (!vis[v]) {
            getAns(v, c, 1, false);
            getAns(v, c, 1, true);
        }
        fill(cnt.begin() + 1, cnt.begin() + mxd + 1, 0);
        for (int v : g[c]) if (!vis[v]) build(v, c, 0);
        rt = c;
    }
};

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n;
    cin >> n;
    vector<vector<int>> g(n);
    int k;
    cin >> k;
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    CentroidDecomposition c(g, k);
    cout << c.ans << "\n";

    return 0;
}