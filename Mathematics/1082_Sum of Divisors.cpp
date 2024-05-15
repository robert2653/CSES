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
// n/1*1 + n/2*2 + ... + n/n*n
// 1:20, 2:10...
// 20,10,6,5,4,3,2,2,2,2,1,1,1,1,1,1,1,1,1,1
ll quick_pow(ll a, ll b){
    ll ans = 1;
    a %= MOD;   b %= MOD;
    while(b > 0){
        if(b & 1){
            ans = (ans * a) % MOD;
        }
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}
ll quick_mul(ll a, ll b){
    ll ans = 0;
    a %= MOD;   b %= MOD;
    while(b > 0){
        if(b & 1){
            ans = (ans + a) % MOD;
        }
        a = (a << 1) % MOD;
        b >>= 1;
    }
    return ans;
}
void solve(){
    ll n; cin >> n;
    ll start = 1, end = n;
    ll ans = 0;
    // mod 1/2 get TLE
    while (start <= end){
        ll div = n / start;
        ll last_same = n / div;
        ll tmp = quick_mul(quick_mul(div, quick_mul(last_same - start + 1, last_same + start)), 500000004);
        (ans += tmp) %= MOD;
        start = last_same + 1;
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