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
#define init(x) memset(x, 0, sizeof(x));
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
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll inf = LLONG_MAX;
const int intf = INT_MAX;
const ll minf = -1e18;
const int maxn = 2505;

int m, n;
vector<edge> graph;
vll adj[maxn];
vl rev_adj[maxn];
ll dis[maxn];
bool vis[maxn] = {0};
bool nvis[maxn] = {0};
void dfs(int par, int now){
    if(vis[now] == 1) return;
    vis[now] = 1;
    for(auto [i, w] : adj[now]){
        if(i != par){
            dfs(now, i);
        }
    }
}
void rev_dfs(int par, int now){
    if(nvis[now] == 1) return;
    nvis[now] = 1;
    for(auto i : rev_adj[now]){
        if(i != par){
            rev_dfs(now, i);
        }
    }
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        graph.push_back({u, v, w});
        adj[u].push_back({v, w});
        rev_adj[v].push_back(u);

    }
    rep(i, 1, n) dis[i] = minf;
    dis[1] = 0;
    rep(i, 1, n){
        for(auto [u, v, w] : graph){
            if(dis[u] + w > dis[v]){
                dis[v] = dis[u] + w;
            }
        }
    }
    dfs(0, 1);
    rev_dfs(0, n);
    for(auto [u, v, w] : graph){
        if(dis[u] + w > dis[v] && nvis[u] && nvis[v] && vis[u] && vis[v]){
            cout << -1;
            return;
        }
    }
    cout << dis[n];
}
int main(){
    IO;
    solve();
}