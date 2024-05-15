// rec-dijkstra
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
typedef pair<ll, ll> pll; typedef pair<int, int> pii;
typedef vector<ll> vl; typedef vector<int> vi;
typedef vector<pll> vll; typedef vector<pii> vii;
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll inf = LLONG_MAX;
const int intf = INT_MAX;
const int maxn = 2e5+5;
vii graph[maxn];
int n, m;
int dis[maxn];
int par[maxn];
bool vis[maxn];
void out(){
    int now = n;
    deque<int> dq;
    while(now != 1){
        dq.push_front(now);
        now = par[now];
    }
    dq.push_front(1);
    for(int i : dq){
        cout << i << " ";
    }
}
void dijkstra(){
    init(vis);
    rep(i, 1, n) dis[i] = intf;
    dis[1] = 1;
    priority_queue<pii, vii, greater<pii>> pq;
    pq.push({0, 1}); // wei, src
    while(!pq.empty()){
        pii tmp = pq.top(); pq.pop();
        int now = tmp.second;
        if(vis[now]) continue;
        for(auto [nei, wei] : graph[now]){
            if(dis[nei] > dis[now]+wei){
                dis[nei] = dis[now] + wei;
                pq.push({dis[nei], nei});
                par[nei] = now;
            }
        } 
    }
    
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back({v, 1});
        graph[v].push_back({u, 1}); // to, weight
    }
    dijkstra();
    if(dis[n] == intf) cout << "IMPOSSIBLE";
    else {
        cout << dis[n] << endl;
        out();
    }
}
int main(){
    IO;
    solve();
}