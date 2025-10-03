#include <bits/stdc++.h>
using namespace std;

const int N = 2E5;
const int Lg = __lg(N);
int cht[N][Lg + 1];
struct FuntionalGraph {
    int n, cnt;
    vector<int> g, bel, id, cycsz, in, top, hei;
    FuntionalGraph(const vector<int> &g) : n(g.size()), cnt(0), g(g), bel(n, -1), id(n), in(n), top(n, -1), hei(n) {
        for (int i = 0; i < n; i++)
            cht[i][0] = g[i], in[g[i]]++;
        for (int i = 1; i <= Lg; i++)
            for (int u = 0; u < n; u++) {
                int nxt = cht[u][i - 1];
                cht[u][i] = cht[nxt][i - 1];
            }
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
        for (int i = 0; i < (int)cyc.size(); i++)
            bel[cyc[i]] = cnt, id[cyc[i]] = i, hei[cyc[i]] = cyc.size();
        if (!cyc.empty())
            ++cnt, cycsz.push_back(cyc.size());
        for (int i = p.size() - 1; i > 0; i--)
            id[p[i - 1]] = id[p[i]] - 1, hei[p[i - 1]] = hei[p[i]] + 1;
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
            cout << (g.id[v] - g.id[u] + g.cycsz[g.bel[u]]) % g.cycsz[g.bel[u]] << "\n";
        } else if (g.bel[u] == -1 && g.bel[v] == -1) {
            if (g.id[u] > g.id[v]) {
                cout << -1 << "\n";
            } else if (g.jump(u, g.id[v] - g.id[u]) == v) {
                cout << g.id[v] - g.id[u] << "\n";
            } else {
                cout << -1 << "\n";
            }
        } else if (g.bel[u] == -1 && g.bel[v] != -1) {
            int len = 0;
            for (int b = Lg; b >= 0; b--) {
                if (g.bel[cht[u][b]] != g.bel[v]) {
                    u = cht[u][b];
                    len |= 1 << b;
                }
            }
            if (g.bel[cht[u][0]] == g.bel[v]) {
                int entrance = cht[u][0];
                cout << len + 1 + (g.id[v] - g.id[entrance] + g.cycsz[g.bel[v]]) % g.cycsz[g.bel[v]] << "\n";
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