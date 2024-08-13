#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int>
using namespace std;
using ll = long long;

struct VBCC {
    int n, cur;
    vector<vector<int>> adj;
    vector<int> dfn, low, parent;
    vector<bool> is_cut;
    VBCC(int n) {
        init(n);
    }
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        parent.assign(n, -1);
        is_cut.assign(n, false);
        cur = 0;
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void dfs(int x) {
        int children = 0;
        dfn[x] = low[x] = cur++;
        
        for (int v : adj[x]) {
            if (dfn[v] == -1) {
                children++;
                parent[v] = x;
                dfs(v);
                low[x] = min(low[x], low[v]);
                
                if (parent[x] != -1 && low[v] >= dfn[x]) {
                    is_cut[x] = true;
                }
            } else if (v != parent[x]) {
                low[x] = min(low[x], dfn[v]);
            }
        }
        if (parent[x] == -1 && children > 1) {
            is_cut[x] = true;
        }
    }
    void work() {
        for (int i = 0; i < n; i++) {
            if (dfn[i] == -1) {
                dfs(i);
            }
        }
    }
};

void solve() {
    int n; cin >> n;
    VBCC g(n);
    int m; cin >> m;
    set<pair<int, int>> appear;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
        appear.insert({u, v});
    }
    g.work();

    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (g.is_cut[i]) {
            ans.push_back(i + 1);
        }
    }
    cout << ans.size() << "\n";
    for (auto i : ans) {
        cout << i << " ";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}