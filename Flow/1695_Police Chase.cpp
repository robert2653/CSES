#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
const int inf = 2e9;
#define int long long
struct edge {
    int v, w, rev_id;
};
int n, m, ans = 0;
vector<edge> adj[505];
vector<int> lev(505), vis(505);
int g[505][505];
bool label_level(){ // 標記深度，如果到不了終點 return false
    fill(all(lev), -1); lev[1] = 0;
    queue<int> q;   q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto i : adj[u]) {
            if (i.w > 0 && lev[i.v] == -1) {
                q.push(i.v);
                lev[i.v] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if (u == n) return flow;
    for (auto &i : adj[u]) {
        if (lev[i.v] == lev[u] + 1 && !vis[i.v] && i.w > 0) {
            vis[i.v] = true;
            int ret = dfs(i.v, min(flow, i.w));
            if (ret > 0) {
                i.w -= ret;
                adj[i.v][i.rev_id].w += ret;
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會 return 0
}
void add_edge(int u, int v, int w) {
    adj[u].push_back({v, w, (int)adj[v].size()});
    adj[v].push_back({u, w, (int)adj[u].size() - 1});
    g[u][v] = g[v][u] = 1;
}
void dinic() {
    while (label_level()) {
        while (true) {
            fill(all(vis), 0);
            int tmp = dfs(1, inf);
            if (tmp == 0) break;
            ans += tmp;
        }
    }
}

void solve(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        add_edge(u, v, 1);
    }
    unordered_set<int> reach;
    auto find = [&](auto self, int u) -> void {
        if (!vis[u]) {
            vis[u] = 1;
            reach.insert(u);
            for (auto [v, w, _] : adj[u]){
                if(w > 0){
                    self(self, v);
                }
            }
        }
    };
    dinic();
    fill(all(vis), 0);
    find(find, 1);
    cout << ans << "\n";
    for (auto u : reach) {
        for (auto [v, w, _] : adj[u]) {
            if (g[u][v] && !w && reach.find(v) == reach.end()) {
                cout << u << " " << v << "\n";
                // ans = sum(u_to_v)
            }
        }
    }
}
signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}