#include <bits/stdc++.h>
// 最大距離，使用拓樸，確保不會再被走過，並且用queue做到類似bfs
// 如果1走不到n，dis[n]!=-inf，而是<0，因為還是可能會被鬆弛
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
const int minf = INT_MIN;
const int maxn = 1e5+5;


void print_ans(int n, vector<int> &par){
    deque<int> ans;
    int now = n;
    while(now != 1){
        ans.push_front(now);
        now = par[now];
    }
    ans.push_front(1);
    cout << ans.size() << endl;
    for(auto i : ans){
        cout << i << " ";
    }
}
void solve(){
    int n, m;
    cin >> n >> m;
    // int dis[maxn];
    vector<int> dis(n+1, -inf); dis[1] = 0;
    vi graph[n+1];
    vector<bool> vis(n+1, 0);
    vector<int> par(n+1);
    vector<int> in(n+1, 0);
    // priority_queue<pii, vii, greater<pii>> pq;
    queue<int> q;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        in[v]++;
    }
    // q.push({0, 1});
    rep(i, 1, n){
        if(in[i] == 0) q.push(i);
    }
    while(!q.empty()){
        // auto [w, u] = q.front(); q.pop();
        int u = q.front(); q.pop();
        // if(dis[u] < w) continue;
        for(auto nxt : graph[u]){
            if(dis[nxt] < dis[u] + 1){
                dis[nxt] = dis[u] + 1;
                // q.push({dis[nxt], nxt});
                par[nxt] = u;
            }
            in[nxt]--; if(in[nxt] == 0) q.push(nxt);
        }
        vis[u] = 1;
    }
    if(dis[n] < 0){
        cout << "IMPOSSIBLE";
    }
    else print_ans(n, par);
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}