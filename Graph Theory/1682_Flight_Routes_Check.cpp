#include <bits/stdc++.h>
// 能去所有+能被所有來
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define rep(i, st, n) for(int i = st; i < n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define pp pop()
#define tp top()
#define ph(x) push(x)
#define IO ios_base::sync_with_stdio(0); cin.tie();
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;

vi graph[100005];
vi rev_graph[100005];
vector<bool> vis(100005, false);
vector<bool> be_vis(100005, false);
int n, m;
void dfs(int src){
    for(auto i : graph[src]){
        if(vis[i]) continue;
        vis[i] = true;
        dfs(i);
    }
}
void rev_dfs(int src){
    for(auto i : rev_graph[src]){
        if(be_vis[i]) continue;
        be_vis[i] = true;
        rev_dfs(i);
    }
}
int main(){
    cin >> n >> m;
    rep(i, 0, m){
        int a, b; cin >> a >> b;
        graph[a].pb(b);
        rev_graph[b].pb(a);
    }
    vis[1] = true; be_vis[1] = true;
    dfs(1); rev_dfs(1);
    bool is = true;
    rep(i, 1, n+1){
        if(!vis[i]) {
            cout << "NO" << endl;
            cout << 1 << " " << i;
            is = false;
            break;
        }
        else if(!be_vis[i]) {
            cout << "NO" endl;
            cout << i << " " << 1;
            is = false;
            break;
        }
    }
    if(is) cout << "YES";
}