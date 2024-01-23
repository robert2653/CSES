// 二分圖最大匹配
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define lrep(i, st, n) for(int i = st; i < n; i++)
#define rep(i, st, n) for(int i = st; i <= n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define init(x, k) memset(x, k, sizeof(x));
#define vec_init(x, k) lrep(i, 0, x.sz){x[i] = k;}
#define lp 2*now
#define rp 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vll;
// typedef struct {
//     int from; int to;
//     ll weight;
// } edge;
typedef struct {
    ll sum;
} Node;
typedef struct {
    int to, w, rev_ind;
} edge;
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
vector<edge> adj[1005];
ll ans = 0;
bool vis[1005];
int lev[1005];
int boy, girl, n, m;
bool dfs(int u){
    if(u == n+1) return true;
    for(auto &i : adj[u]){
        bool flag = 0;
        if(!vis[i.to] && i.w > 0) {
            vis[i.to] = true;
            flag = dfs(i.to);
            if(flag) {
                i.w -= 1;
                adj[i.to][i.rev_ind].w += 1;
                return true;
            }
        }
    }
    return false;   // 到不了終點就會return 0
}
void Print_ans(){
    vector<pii> ans;
    rep(i, 1, boy){
        for(auto u : adj[i]){
            if(u.w == 0 && u.to != 0){
                // cout << i << " " << u.to-boy << endl;
                ans.push_back({i, u.to-boy});
            }
        }
    }
    cout << ans.sz << endl;
    for(auto [u, v] : ans){
        cout << u << " " << v << endl;
    }
}
void solve(){
    cin >> boy >> girl >> m;
    n = boy + girl;
    rep(i, 1, boy){
        adj[0].push_back({i, 1, (int)adj[i].sz});
        adj[i].push_back({0, 0, (int)adj[0].sz-1});
    }
    rep(i, boy+1, boy+girl){
        adj[i].push_back({n+1, 1, (int)adj[n+1].sz});
        adj[n+1].push_back({i, 0, (int)adj[i].sz-1});
    }
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        v += boy;
        adj[u].push_back({v, 1, (int)adj[v].sz});   // 反向流的ind
        adj[v].push_back({u, 0, (int)adj[u].sz-1}); // 已經push一個了，要-1
    }
    while(1){
        init(vis, 0);
        vis[0] = true;
        if(!dfs(0)) break;
    }
    Print_ans();
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}