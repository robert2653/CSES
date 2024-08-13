#include <bits/stdc++.h>
using namespace std;

constexpr int N = 2e5 + 5;
int cht[N][31]; // 倍增表, 放外面不然 TLE
struct FuntionalGraph {
    int n, cnt;
    vector<int> g, bel, id, len, in, top;
    FuntionalGraph() : n(0) {}
    FuntionalGraph(vector<int> g_) { init(g_); }
    void init(vector<int> g_) {
        n = g_.size(); cnt = 0;
        g = g_; bel.assign(n, -1);
        id.resize(n); len.clear();
        in.assign(n, 0); top.assign(n, -1);
        build();
    }
    void build() {
        for (int i = 0; i < n; i++) {
            cht[i][0] = g[i];
            in[g[i]]++;
        }
        for (int i = 1; i <= 30; i++)
            for (int u = 0; u < n; u++)
                cht[u][i] = cht[cht[u][i - 1]][i - 1];
        for (int i = 0; i < n; i++)
            if (in[i] == 0) label(i);
        for (int i = 0; i < n; i++)
            if (top[i] == -1) label(i);
    }
    void label(int u) {
        vector<int> p; int cur = u;
        while (top[cur] == -1) {
            top[cur] = u;
            p.push_back(cur);
            cur = g[cur];
        }
        auto s = find(p.begin(), p.end(), cur);
        vector<int> cyc(s, p.end());
        p.erase(s, p.end()); p.push_back(cur);
        for (int i = 0; i < (int)cyc.size(); i++) {
            bel[cyc[i]] = cnt;
            id[cyc[i]] = i;
        }
        if (!cyc.empty())
            ++cnt, len.push_back(cyc.size());
        for (int i = p.size() - 1; i > 0; i--)
            id[p[i - 1]] = id[p[i]] - 1;
    }
    int jump(int u, int k) {
        for (int b = 0; k > 0; b++){
            if (k & 1) u = cht[u][b];
            k >>= 1;
        }
        return u;
    }
};

void solve(){
    int n, q;
    cin >> n >> q;
    vector<int> init(n);
    for (int i = 0; i < n; i++) {
        cin >> init[i];
        init[i]--;
    }
    FuntionalGraph g(init);
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (g.bel[u] == g.bel[v] && g.bel[u] != -1 && g.bel[v] != -1) {
            cout << (g.id[v] - g.id[u] + g.len[g.bel[u]]) % g.len[g.bel[u]] << "\n";
        } else if (g.bel[u] == -1 && g.bel[v] == -1) {
            if (g.id[u] > g.id[v]) {
                cout << -1 << "\n";
            } else if (g.jump(u, g.id[v] - g.id[u]) == v) {
                cout << g.id[v] - g.id[u] << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (g.bel[u] == -1 && g.bel[v] != -1) {
            int l = 0, r = n;
            while (l <= r) {
                int m = (l + r) / 2;
                if (g.bel[g.jump(u, m)] == g.bel[v]) {
                    r = m - 1;
                } else {
                    l = m + 1;
                }
            }
            if (l < n) {
                int entrance = g.jump(u, l);
                cout << l + (g.id[v] - g.id[entrance] + g.len[g.bel[v]]) % g.len[g.bel[v]] << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else {
            cout << -1 << "\n";
        }
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    while (t--) {
        solve();
    }
}