// 把每個scc重新建一個dag，然後拓樸dp
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
const int maxn = 1e5+5;

vector<int> adj[maxn], rev_adj[maxn];
int order[maxn];
int k = 0;
vector<int> DAG[maxn];
int coin[maxn];
int n, m;
bool vis[maxn];
vector<int> v;
int in[maxn];
void dfs(int now){
    if(!vis[now]){
        vis[now] = 1;
        for(auto i : adj[now]){
            dfs(i);
        }
        v.push_back(now);
    }
}
void rev_dfs(int now){
    if(!vis[now]){
        vis[now] = 1;
        order[now] = k;
        for(auto i : rev_adj[now]){
            rev_dfs(i);
        }
    }
}
void solve(){
    cin >> n >> m;
    rep(i, 1, n){
        cin >> coin[i];
    }
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        adj[u].push_back(v);
        rev_adj[v].push_back(u);
    }
    rep(i, 1, n){
        if(!vis[i]){
            dfs(i);
        }
    }
    reverse(all(v));
    init(vis, 0);
    for(auto i : v){
        if(!vis[i]){
            k++;
            rev_dfs(i);
        }
    }
    // 分類完scc
    ll sum_coin[k+1], dp_coin[k+1];
    init(sum_coin, 0); init(dp_coin, 0);
    ll ans = -inf;
    rep(i, 1, n){
        sum_coin[order[i]] += coin[i];   // 當組+=coin;
        for(auto j : adj[i]){
            if(order[i] != order[j]){
                DAG[order[i]].push_back(order[j]);
                in[order[j]]++;
            }
        }
    }
    // 拓樸dp
    queue<int> q;
    rep(i, 1, k){
        if(in[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int now = q.front(); q.pop();
        dp_coin[now] += sum_coin[now];
        ans = max(ans, dp_coin[now]);
        for(auto v : DAG[now]){
            in[v]--;
            dp_coin[v] = max(dp_coin[v], dp_coin[now]);
            if(in[v] == 0) q.push(v);
        }
    }
    cout << ans;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}