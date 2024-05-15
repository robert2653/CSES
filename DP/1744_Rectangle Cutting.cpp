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
const int maxn = 505;
ll dp[maxn][maxn];
void solve(){
    for(int i = 0; i < 505; i++){
        for(int j = 0; j < 505; j++){
            dp[i][j] = llinf;
        }
    }
    int a, b; cin >> a >> b;
    rep(i, 1, a){
        rep(j, 1, b){
            if(i == j){
                dp[i][j] = 0;
                continue;
            }
            // 看要切哪裡
            for(int k = 1; k < i; k++){ // 切i
                dp[i][j] = min(dp[i][j], dp[k][j] + dp[i-k][j] + 1);
            }
            for(int k = 1; k < j; k++){ // 切j
                dp[i][j] = min(dp[i][j], dp[i][j-k] + dp[i][k] + 1);
            }
        }
    }
    cout << dp[a][b];
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}