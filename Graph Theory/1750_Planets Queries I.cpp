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
int n, q;
void solve(){
    cin >> n >> q;
    // int tel[n+1];
    // map<int, int> circle;
    int chart[n+1][32];
    rep(u, 1, n){
        int v; cin >> v;
        // tel[u] = v;
        chart[u][0] = v;
    }
    rep(j, 1, 31){
        rep(i, 1, n){
            chart[i][j] = chart[chart[i][j-1]][j-1];
        }
    }
    int u, k; 
    rep(i, 1, q){
        cin >> u >> k;
        for(int bit = 0; k > 0; bit++){
            if(k & 1) u = chart[u][bit];
            k >>= 1;
        }
        cout << u << endl;
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