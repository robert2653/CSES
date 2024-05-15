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
const int maxn = 2e5+5;
ll dp[505][63000]; 
// ll dp[505][100];
ll nxt(){
    ll x; cin >> x;
    return x;
}
void solve(){
    int n = nxt();
    ll x = (n + 1) * n / 2;
    if(x & 1){
        cout << 0;
        return;
    }
    x /= 2;
    init(dp, 0);
    dp[0][0] = 1;
    rep(i, 1, n){
        rep(j, 0, x){
            dp[i][j] = dp[i-1][j];
            if(j >= i){
                dp[i][j] = (dp[i][j] + dp[i-1][j-i]) % MOD;
            }
        }
    }
    cout << dp[n-1][x]; // 其中一組sum = ans, 剩下的 +n = ans
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}