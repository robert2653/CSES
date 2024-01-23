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
const int maxn = 1e5+5;

int n, m;
ll dis[maxn];
vll graph[maxn];
bool vis[maxn];
void dijkstra(int src){
    init(vis);
    priority_queue<pll, vll, greater<pll>> pq;
    rep(i, 1, n){
        dis[i] = inf;
    }
    pq.push({0, 1});
    dis[1] = 0;
    while(!pq.empty()){
        pll now = pq.top(); pq.pop();
        ll u = now.second;
        // if(!vis[u]){
        if(dis[u] < now.first) continue;
        if(1){
            for(auto i : graph[u]){
                if(dis[u] + i.second < dis[i.first]){
                    dis[i.first] = dis[u] + i.second;
                    pq.push({dis[i.first], i.first});
                }
            }
        }
        vis[u] = true;
    }
    rep(i, 1, n){
        cout << dis[i] << " ";
    }
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    dijkstra(1);
}
int main(){
    IO;
    solve();
}