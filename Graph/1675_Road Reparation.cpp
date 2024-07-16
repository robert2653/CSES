// Prim
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
ll ans = 0;
vii adj[maxn];
bool Prim(){
    int node_sz = 0;
    priority_queue<pii, vii, greater<pii>> pq;
    pq.push({0, 1});
    bool vis[maxn]; init(vis, false);
    while(!pq.empty()){
        auto [cost, u] = pq.top(); pq.pop();
        if(vis[u]) continue;
        vis[u] = true;
        ans += cost;
        node_sz++;
        for(auto [v, cost] : adj[u]){
            if(!vis[v])
                pq.push({cost, v});
        }
    }
    if(node_sz == n) return true;
    return false;
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v, cost; cin >> u >> v >> cost;
        adj[u].push_back({v, cost});
        adj[v].push_back({u, cost});
    }
    if(Prim()) cout << ans;
    else cout << "IMPOSSIBLE";
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}