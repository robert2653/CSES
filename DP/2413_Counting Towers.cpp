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
const int maxn = 1e6+5;

ll dp[maxn][2]; // 1是放橫
void query(int h){
    cout << (dp[h][0] + dp[h][1]) % MOD << endl;
}
void solve(){
    int q; cin >> q;
    dp[1][0] = 1, dp[1][1] = 1;
    rep(i, 2, 1000000){
        dp[i][0] = (dp[i][0] + (dp[i-1][0] * 4 % MOD)) % MOD;
        dp[i][0] = (dp[i][0] + dp[i-1][1]) % MOD;   // 兩圈
        dp[i][1] = (dp[i-1][0] + (dp[i-1][1] * 2 % MOD)) % MOD; 
    }
    rep(i, 1, q){
        int h; cin >> h;
        query(h);
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