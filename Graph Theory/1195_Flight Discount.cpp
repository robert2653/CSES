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
    ll w; ll u;
    ll discount;
} edge;
typedef struct {
    ll sum;
} Node;
const ll inf = LLONG_MAX;
const int intf = INT_MAX;
const int maxn = 1e5+5;
int n, m;
vll graph[maxn];
ll dis[maxn][2];    // 0 for not used
void dijkstra(){
    priority_queue<vector<ll>, vector<vector<ll>>, greater<vector<ll>>> pq;  // 0 for w, 1 for u, 2 for discount
    rep(i, 1, n){
        dis[i][0] = dis[i][1] = inf;
    }
    dis[1][0] = dis[1][1] = 0;
    pq.push({0, 1, 0});
    while(!pq.empty()){
        auto nxt = pq.top(); pq.pop();
        ll dist = nxt[0], u = nxt[1]; bool us = nxt[2];
        if(dis[u][us] < dist) continue; // 過時了，跳過
        if(us){
            for(auto [v, w] : graph[u]){
                if(dis[u][1] + w < dis[v][1]){
                    dis[v][1] = dis[u][1] + w;
                    pq.push({dis[v][1], v, 1});
                }
            }
        }
        else {
            for(auto [v, w] : graph[u]){
                if(dis[u][0] + w < dis[v][0]){
                    dis[v][0] = dis[u][0] + w;
                    pq.push({dis[v][0], v, 0});
                }
                if(dis[u][0] + w / 2 < dis[v][1]){
                    dis[v][1] = dis[u][0] + w / 2;
                    pq.push({dis[v][1], v, 1});
                }
            }
        }
    }
    cout << min(dis[n][0], dis[n][1]);
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v, w;
        cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    dijkstra();
}
int main(){
    IO;
    solve();
}