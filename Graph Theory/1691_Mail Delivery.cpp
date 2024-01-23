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
set<int> sorted_adj[maxn];
// 思路: 把每個節點當成環的起點
void find_road(int now, vector<int> &ans){
    while(sorted_adj[now].size()){
        int nxt = *sorted_adj[now].begin();
        sorted_adj[now].erase(nxt);
        sorted_adj[nxt].erase(now);
        find_road(nxt, ans);
    }
    ans.push_back(now);
}
void solve(){
    int n, m;   cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        sorted_adj[u].insert(v);
        sorted_adj[v].insert(u);
    }
    // 檢查每個vertex的out_degree是否為odd
    rep(i, 1, n){
        if(sorted_adj[i].size() % 2){
            cout << "IMPOSSIBLE";
            return;
        }
    }
    vector<int> ans;
    find_road(1, ans);
    if(ans.size() != m+1){
        cout << "IMPOSSIBLE";
        return;
    }
    else {
        reverse(all(ans));
        for(auto i : ans){
            cout << i << " ";
        }
    }
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}