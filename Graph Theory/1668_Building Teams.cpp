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
vector<int> graph[maxn];
vector<int> col(maxn);
vector<bool> vis(maxn);
bool dfs(int now, int color){
    bool flag = true;
    col[now] = color;
    vis[now] = 1;
    for(auto i : graph[now]){
        if(col[now] == col[i]) flag = false;
        if(!vis[i]){
            if(col[now] == 1) flag *= dfs(i, 2);
            else flag *= dfs(i, 1);
        }
    }
    return flag;
}
void solve(){
    int n, m; cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    bool flag = 1;
    rep(i, 1, n){
        if(!col[i]){
            flag *= dfs(i, 1);
            if(!flag){
                cout << "IMPOSSIBLE" << endl;
                return;
            }
        }
    }
    rep(i, 1, n){
        if(col[i]){
            cout << col[i] << " ";
        }
        else cout << 2 << " ";  // 隨便
    }
}
int main(){
    IO;
    solve();
}