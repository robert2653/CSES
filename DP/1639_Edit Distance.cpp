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
    init(dp, 0);
    string s1, s2; cin >> s1 >> s2;
    int size1 = s1.sz, size2 = s2.sz;
    s1 = "0" + s1, s2 = "0" + s2;
    rep(i, 1, size2) dp[0][i] = i;  // s2 = {}, s1 = ...;
    rep(i, 1, size1) dp[i][0] = i;  // s1 = {}, s2 = ...;
    rep(i, 1, size1){
        rep(j, 1, size2){
            if(s1[i] == s2[j]){
                dp[i][j] = dp[i-1][j-1];
            }
            else {
                dp[i][j] = min(min(dp[i-1][j-1], dp[i-1][j]), dp[i][j-1]) + 1;
                                // 修改    // s1 del / s2 add   // s1 add s2 del  
            }
        }
    }
    cout << dp[size1][size2];
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}