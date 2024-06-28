// Dinic
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define int long long
struct edge {
    int v, w, rev_id, arg_valid;
};
const int inf = 2e9;
int n, m, ans = 0;
vector<edge> adj[505];
vector<int> lev(505), vis(505);
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
    for (auto &[v, w, rev_id, arg_valid] : adj[u]){
        if (lev[v] == lev[u] + 1 && !vis[v] && w > 0) {
            vis[v] = true;
            int ret = dfs(v, min(flow, w));
            if (ret > 0) {
                w -= ret;
                adj[v][rev_id].w += ret;
                if (arg_valid) {    // 走的是 arg 路，Reset
                    arg_valid = 0;
                    adj[v][rev_id].arg_valid = 0;
                }
                else adj[v][rev_id].arg_valid = 1;    // 走正常路
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會 return 0
}
bool get_road(int now, vector<int> &ans, vector<bool> &vis) {
    if (now == 1) return true;
    for (auto &[v, w, rev_id, arg_valid] : adj[now]) {
        if (arg_valid && !vis[v]){
            ans.push_back(v);
            vis[v] = true;
            bool flag = get_road(v, ans, vis);
            if (flag) {
                arg_valid = false;
                return true;
            }
            ans.pop_back();
        }
    }
    return false;
}
void solve(){
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        adj[u].push_back({v, 1, (int)adj[v].size(), 0});   // 反向流的 ind
        adj[v].push_back({u, 0, (int)adj[u].size() - 1, 0}); // 已經 push 一個了，要 -1
    }
    while (label_level()) {
        while (true) {
            fill(all(vis), 0);
            int tmp = dfs(1, inf);
            if (tmp == 0) break;
            ans += tmp;
        }
    }
    cout << ans << "\n";
    for (int i = 0; i < ans; i++) {
        vector<int> ans = {n};
        vector<bool> vis(n+1, false);
        get_road(n, ans, vis);
        cout << ans.size() << endl;
        for(auto it = ans.rbegin(); it != ans.rend(); it++){
            cout << *it << " ";
        }
        cout << "\n";
    }
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