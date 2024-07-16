// 前k最短路徑
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
const int maxn = 2e5+5;


vll graph[maxn];
void solve(){
    int n, m, k;
    cin >> n >> m >> k;
    rep(i, 1, m){
        int u, v, w; cin >> u >> v >> w;
        graph[u].push_back({v, w});
    }
    priority_queue<pll, vll, greater<pll>> pq;
    pq.push({0, 1});
    priority_queue<ll> dis[n+1];
    dis[1].push(0);
    while(!pq.empty()){
        auto [w, u] = pq.top(); pq.pop();
        if(dis[u].top() < w) continue;
        for(auto [nxt_ind, nxt_w] : graph[u]){
            if(dis[nxt_ind].size() < k){    // 不夠數量，不管丟就對了
                pq.push({w + nxt_w, nxt_ind});
                dis[nxt_ind].push(w + nxt_w);
            }
            else if(dis[nxt_ind].top() > w + nxt_w){    // 把最大的鬆弛
                dis[nxt_ind].pop();
                dis[nxt_ind].push(w + nxt_w);
                pq.push({w + nxt_w, nxt_ind});
            }
        }
    }
    vector<ll> ans;
    while(k--){
        ans.push_back(dis[n].top());
        dis[n].pop();
    }
    for(auto it = ans.rbegin(); it != ans.rend(); it++){
        cout << *it << " ";
    }
}
int main(){
    IO;
    solve();
}