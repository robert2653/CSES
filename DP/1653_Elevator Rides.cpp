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
void solve(){
    int n, x; cin >> n >> x;
    int s[n];
    lrep(i, 0, n){
        cin >> s[i];
    }
    vector<int> used(1 << n, 0);
    vector<ll> dp(1 << n, 1);  // bitset
    for(int i = 1; i < 1 << n; i++){
        used[i] = dp[i] = inf;
        for(int j = 0; j < n; j++){
            if(i & (1 << j)){  // 有j
                int last = i ^ (1 << j);
                if(used[last] + s[j] <= x){
                    if(dp[last] < dp[i] || dp[last] == dp[i] && used[last] + s[j] < used[i]){
                        used[i] = used[last] + s[j];
                        dp[i] = dp[last];
                    }
                }
                else {
                    if(dp[last] + 1 < dp[i] || dp[last] + 1 == dp[i] && s[j] < used[i]){
                        used[i] = s[j];
                        dp[i] = dp[last] + 1;
                    }
                }
            }
        }
    }
    cout << dp[(1 << n) - 1];
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}