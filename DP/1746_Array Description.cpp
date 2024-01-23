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
int dp[100005][105];
void solve(){
    int n, up; cin >> n >> up;
    // lrep(i, 1, 105) memset(dp[i], 0, sizeof(dp[i]));
    int x1; cin >> x1;
    if(x1 == 0) {
        rep(i, 1, up) dp[1][i] = 1; // arbitrary number
    }
    else dp[1][x1] = 1; // only one
    rep(i, 2, n){
        int x; cin >> x;
        if(x == 0){
            rep(j, 1, up){
                for(int last : {j-1, j, j+1}){
                    if(last >= 1 && last <= up){
                        dp[i][j] += dp[i-1][last];
                        dp[i][j] %= MOD;
                    }
                }
            }
        }
        else {
            for(int last : {x-1, x, x+1}){
                if(last >= 1 && last <= up){
                    dp[i][x] += dp[i-1][last];
                    dp[i][x] %= MOD;
                }
            }
        }
    }
    ll ans = 0;
    rep(i, 1, up){
        ans += dp[n][i];
        ans %= MOD;
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