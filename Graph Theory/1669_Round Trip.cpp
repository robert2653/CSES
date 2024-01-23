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
int boss[maxn];
int set_sz[maxn];
int n, m;
int parent[maxn];
vector<int> ans;
vector<int> graph[maxn];
bool vis[maxn];
int inter;
int find_boss(int now){
    if(boss[now] != now){
        return boss[now] = find_boss(boss[now]);
    }
    return boss[now];
}
void dfs(int now, int par){
    vis[now] = true;
    parent[now] = par;
    for(auto nxt : graph[now]){
        if(nxt == par) continue;
        if(!vis[nxt]){
            dfs(nxt, now);
        }
        else {  // 找到環了
            int copnow = now;
            while(copnow != nxt){
                ans.push_back(copnow);
                copnow = parent[copnow];
            }
            ans.push_back(nxt); ans.push_back(now);
            cout << ans.size() << endl;
            for(auto i : ans) cout << i << " ";
            exit(0);
        }
    }
}
void MST(int u, int v){
    int boss_u = find_boss(u);
    int boss_v = find_boss(v);
    if(boss_u != boss_v){
        if(set_sz[boss_u] > set_sz[boss_v]) swap(boss_u, boss_v);
        boss[boss_u] = boss_v;
        set_sz[boss_v] += set_sz[boss_v];
    }
    else {
        dfs(u, v);
    }
}
void solve(){
    cin >> n >> m;
    rep(i, 1, n){
        boss[i] = i;
        set_sz[i] = 1;
    }
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
        MST(u, v);
    }
    cout << "IMPOSSIBLE";
}
int main(){
    IO;
    solve();
}