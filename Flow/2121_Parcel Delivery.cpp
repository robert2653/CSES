// MCMF
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
    int from, to, w, cost;
} edge;

const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
int n, m, parcel;
vector<edge> adj;   // 幫每個edge編號
vector<int> p[505]; // from內存edge編號

int now_edge = 0;
void add_edge(int u, int v, int w, int cost){
    adj.push_back({u, v, w, cost});
    p[u].push_back(now_edge);
    now_edge++;
    adj.push_back({v, u, 0, -cost});
    p[v].push_back(now_edge);
    now_edge++;
}
ll Bellman_Ford(){
    vector<ll> dis(n+1, inf); dis[1] = 0;
    vector<int> par(m);
    vector<int> flow_rec(n+1, 0); flow_rec[1] = 1e9;
    lrep(i, 1, n){
        bool flag = 1;
        int size = adj.sz;
        lrep(i, 0, size){
            auto &[from, to, w, cost] = adj[i];
            if(w > 0 && dis[to] > dis[from] + cost){
                flag = 0;
                dis[to] = dis[from] + cost;
                par[to] = i;   // 紀錄編號
                flow_rec[to] = min(flow_rec[from], w);
            }
        }
        if(flag) break;
    }
    if(dis[n] == 1e9) return 0;
    int mn_flow = flow_rec[n];
    int v = n;
    while(v != 1){
        int u = adj[par[v]].from;
        adj[par[v]].w -= mn_flow;
        adj[par[v] ^ 1].w += mn_flow;
        v = u;
    }
    mn_flow = min(mn_flow, parcel);
    parcel -= mn_flow;
    return mn_flow * dis[n];
}
void solve(){
    cin >> n >> m >> parcel;
    ll ans = 0;
    rep(i, 1, m){
        int u, v, w, cost; cin >> u >> v >> w >> cost;
        add_edge(u, v, w, cost);
    }
    while(parcel > 0){
        int tmp = Bellman_Ford();
        if(tmp == 0) break;
        ans += tmp;
    }
    cout << (parcel > 0 ? -1 : ans);
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}