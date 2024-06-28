// Dinic
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
bool label_level(){ // 標記深度，如果到不了終點 return false
    fill(all(lev), -1); lev[1] = 0;
    queue<int> q;   q.push(1);
    while (!q.empty()) {
        int u = q.front(); q.pop();
        for (auto &[v, w, rev_id] : adj[u]) {
            if (w > 0 && lev[v] == -1) {
                q.push(v);
                lev[v] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if (u == n) return flow;
    for (auto &[v, w, rev_id] : adj[u]) {
        if (lev[v] == lev[u] + 1 && !vis[v] && w > 0) {
            vis[v] = true;
            int ret = dfs(v, min(flow, w));
            if (ret > 0) {
                w -= ret;
                adj[v][rev_id].w += ret;
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會 return 0
}
void solve(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w, (int)adj[v].size()});
        adj[v].push_back({u, 0, (int)adj[u].size() - 1});
    }
    while (label_level()) {
        while (true) {
            fill(all(vis), 0);
            int tmp = dfs(1, inf);
            if (tmp == 0) break;
            ans += tmp;
        }
    }
    cout << ans;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}