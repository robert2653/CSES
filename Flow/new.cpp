#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using pbds_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;

const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;

struct edge {
    int to, w, rev_ind, arg_valid;
};
const int maxn = 2e5+5;
int n, m;
vector<edge> adj[505];
int ans = 0;
bool vis[505];
int lev[505];
bool label_level(){ // 標記深度，如果到不了終點return false
    memset(lev, -1, sizeof(lev));
    lev[1] = 0;
    queue<int> q;   q.push(1);
    while(!q.empty()){
        int u = q.front(); q.pop();
        for(auto i : adj[u]){
            if(i.w > 0 && lev[i.to] == -1){
                q.push(i.to);
                lev[i.to] = lev[u] + 1;
            }
        }
    }
    return (lev[n] == -1 ? false : true);
}
int dfs(int u, int flow){
    if(u == n) return flow;
    for(auto &i : adj[u]){
        if(lev[i.to] == lev[u] + 1 && !vis[i.to] && i.w > 0) {
            vis[i.to] = true;
            int ret = dfs(i.to, min(flow, i.w));
            if(ret > 0) {
                i.w -= ret;
                adj[i.to][i.rev_ind].w += ret;
                if(i.arg_valid){    // 走的是arg路，Reset
                    i.arg_valid = 0;
                    adj[i.to][i.rev_ind].arg_valid = 0;
                }
                else adj[i.to][i.rev_ind].arg_valid = 1;    // 走正常路
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會return 0
}
bool get_road(int now, vector<int> &ans, vector<bool> &vis){
    if(now == 1) return true;
    for(auto &v : adj[now]){
        if(v.arg_valid && !vis[v.to]){
            ans.push_back(v.to);
            vis[v.to] = true;
            bool flag = get_road(v.to, ans, vis);
            if(flag){
                v.arg_valid = false;
                return true;
            }
            ans.pop_back();
        }
    }
    return false;
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        adj[u].push_back({v, 1, (int)adj[v].sz, 0});   // 反向流的ind
        adj[v].push_back({u, 0, (int)adj[u].sz-1, 0}); // 已經push一個了，要-1
    }
    while(label_level()){
        while(1){
            init(vis, 0);
            int tmp = dfs(1, inf);
            if(tmp == 0) break;
            ans += tmp;
        }
    }
    cout << ans << endl;
    rep(i, 1, ans){
        vector<int> ans = {n};
        vector<bool> vis(n+1, false);
        get_road(n, ans, vis);
        cout << ans.sz << endl;
        for(auto it = ans.rbegin(); it != ans.rend(); it++){
            cout << *it << " ";
        }
        cout << endl;
    }
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while(t--){
        solve();
    }
}