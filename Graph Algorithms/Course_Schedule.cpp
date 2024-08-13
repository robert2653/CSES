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

int n, m;
int in[maxn];
vector<int> graph[maxn];
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        in[v]++;
        graph[u].push_back(v);
    }
    queue<int> q;
    vector<int> ans;
    rep(i, 1, n){
        if(in[i] == 0){
            q.push(i);
        }
    }
    while(!q.empty()){
        int now = q.front(); q.pop();
        ans.push_back(now);
        for(auto nxt : graph[now]){
            in[nxt]--;
            if(in[nxt] == 0) q.push(nxt);
        }
    }
    if(ans.size() == n){
        for(auto i : ans) cout << i << " ";
    }
    else cout << "IMPOSSIBLE";
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}