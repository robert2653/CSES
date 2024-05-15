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
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
const int mod = 1e9+7;
int n, m;
void solve(){
    cin >> n >> m;
    vii graph[n+1];
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    vl dis(n+1, llinf); dis[1] = 0;
    vector<bool> vis(n+1, 0);
    vector<ll> min_num(n+1, 0), max_min(n+1, 0), min_min(n+1, 0);   min_num[1] = 1;
    priority_queue<pll, vll, greater<pll>> pq;
    pq.push({0, 1});    min_num[1] = 1;
    while(!pq.empty()){
        auto [no, u] = pq.top(); pq.pop();
        if(vis[u]) continue;
        for(auto [v, w] : graph[u]){
            if(dis[u] + w < dis[v]){
                dis[v] = dis[u] + w;
                pq.push({dis[v], v});
                min_num[v] = min_num[u];
                max_min[v] = max_min[u] + 1;
                min_min[v] = min_min[u] + 1;
            }
            else if(dis[u] + w == dis[v]){
                min_num[v] = (min_num[u] + min_num[v]) % mod;
                max_min[v] = max(max_min[u] + 1, max_min[v]);
                min_min[v] = min(min_min[u] + 1, min_min[v]);
            }
        }
        vis[u] = 1;
    }
    cout << dis[n] << " " << min_num[n] << " " << min_min[n] << " " << max_min[n] << endl;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}