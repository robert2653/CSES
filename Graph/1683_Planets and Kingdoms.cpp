// 從1到n，能去所有跟能被所有到的為一個kingdom
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
const int maxn = 2e5+5;

int n, m;
vi adj[maxn], rev_adj[maxn];
int vis[maxn], be_vis[maxn];
void dfs(int now, int k){
    if(vis[now] != be_vis[now] && vis[now] != k){
        vis[now] = k;
        for(auto i : adj[now]){
            dfs(i, k);
        }
    }
}
void rev_dfs(int now, int k){
    if(vis[now] != be_vis[now] && be_vis[now] != k){
        be_vis[now] = k;
        for(auto i : rev_adj[now]){
            rev_dfs(i, k);
        }
    }
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    init(vis, 0); init(be_vis, -1);
    int now_kd = 0;
    rep(i, 1, n){
        if(vis[i] == be_vis[i]) continue;
        now_kd++;
        dfs(i, now_kd); rev_dfs(i, now_kd);
    }
    cout << now_kd << endl;
    rep(i, 1, n){
        cout << vis[i] << " ";
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