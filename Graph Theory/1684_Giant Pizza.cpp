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
#define init(x, k) lrep(i, 0, sizeof(x)/sizeof(x[0])){x[i] = k;}
#define vec_init(x, k) lrep(i, 0, x.sz){x[i] = k;}
#define lc 2*now
#define rc 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 1e5+5;
vector<int> adj[2*maxn], rev_adj[2*maxn];
vector<int> order;
int cat[2*maxn];
int k = 1;
bool vis[2*maxn];
void dfs(int now){
    if(!vis[now]){
        vis[now] = 1;
        for(auto v : adj[now]){
            dfs(v);
        }
        order.push_back(now);
    }
}
void rev_dfs(int now){
    if(!vis[now]){
        cat[now] = k;
        vis[now] = 1;
        for(auto v : rev_adj[now]){
            rev_dfs(v);
        }
    }
}
void solve(){
    int n, m; cin >> m >> n;
    rep(i, 1, m){
        int u, v; char a, b;
        cin >> a >> u >> b >> v;
        if(a == '-'){
            u = 2 * n - u + 1;  // 反轉
        }
        if(b == '-'){
            v = 2 * n - v + 1;  // 反轉
        }
        adj[2 * n - u + 1].push_back(v);  // -u 到 v;
        adj[2 * n - v + 1].push_back(u);  // -v 到 u;
        rev_adj[v].push_back(2 * n - u + 1);
        rev_adj[u].push_back(2 * n - v + 1);
    }
    rep(i, 1, 2*n){
        if(!vis[i]){
            dfs(i);
        }
    }
    memset(vis, 0, sizeof(vis));
    reverse(all(order));
    for(auto i : order){
        // cout << i << " ";
        if(!vis[i]){
            rev_dfs(i);
            k++;
        }
    }
    char ans[2*n+1];
    rep(i, 1, n){
        // cout << cat[i] << cat[2*n-i+1];
        // cout << "\n";
        if(cat[i] == cat[2*n-i+1]){
            cout << "IMPOSSIBLE";
            return;
        }
        if(cat[i] > cat[2*n-i+1]){
            ans[i] = '+';
        }
        else ans[i] = '-';
    }
    rep(i, 1, n){
        cout << ans[i] << " ";
    }
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}