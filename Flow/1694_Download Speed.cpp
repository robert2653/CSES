// Dinic
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
int n, m;
vector<edge> adj[505];
ll ans = 0;
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
                return ret;
            }
        }
    }
    return 0;   // 到不了終點就會return 0
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        adj[u].push_back({v, w, (int)adj[v].sz});   // 反向流的ind
        adj[v].push_back({u, 0, (int)adj[u].sz-1}); // 已經push一個了，要-1
    }
    while(label_level()){
        while(1){
            init(vis, 0);
            int tmp = dfs(1, inf);
            if(tmp == 0) break;
            ans += tmp;
        }
    }
    cout << ans;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}