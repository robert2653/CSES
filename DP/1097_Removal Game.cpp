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
#define init(x, k) memset(x, k, sizeof(x));
#define vec_init(x, k) x.assign(x.size(), k);
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
const ll llinf = 1e18;
const int inf = 1e9;
const int MOD = 1e9+7;
const int maxn = 5e3+5;
ll dp[maxn][maxn];
void solve(){
    int n; cin >> n;
    ll pref = 0;
    vector<ll> v(n+1);
    rep(i, 1, n){
        cin >> v[i];
        pref += v[i];
    }
    // dp[i][j] = max_diff(i to j);
    for(int i = n; i > 0; i--){
        for(int j = 1; j <= n; j++){
            if(i > j) continue;
            else if(i == j){
                dp[i][j] = v[i];
            }
            else {
                dp[i][j] = max(v[i] - dp[i+1][j], v[j] - dp[i][j-1]);   // i+1, j-1, 注意dp順序
            }
        }
    }
    // x + y = sum, dp[1][n] = x - y;
    cout << (pref + dp[1][n]) / 2;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}