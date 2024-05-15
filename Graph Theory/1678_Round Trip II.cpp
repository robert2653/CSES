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
const int maxn = 1e5+5;

int n, m;
vi graph[maxn];
int color[maxn];
int parent[maxn];
bool vis[maxn];
void print_ans(int ori){
    int now = parent[ori];
    deque<int> ans;
    ans.push_front(ori);
    while(now != ori){
        ans.push_front(now);
        now = parent[now];
    }
    ans.push_front(ori);
    cout << ans.size() << endl;
    for(auto i : ans){
        cout << i << " ";
    }
    exit(0);
}
void dfs(int now){
    color[now] = 1;
    vis[now] = 1;
    for(auto nxt : graph[now]){
        parent[nxt] = now;
        if(color[nxt] == 1){
            print_ans(nxt);
        }
        else if(color[nxt] == 0){
            dfs(nxt);
        }
    }
    color[now] = 2;
}
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
    }
    rep(i, 1, n){
        if(!vis[i])
            dfs(i);
    }
    cout << "IMPOSSIBLE";
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}