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
int n; 
ll from[maxn], to[maxn], gain[maxn];
ll dp[400005];
vll rev_proj[400005];
void compress(map<int, int> mp){
    int now = 0;
    for(auto &i : mp){
        mp[i.first] = ++now;
    }
    rep(i, 1, n){
        rev_proj[mp[to[i]]].push_back({mp[from[i]], gain[i]});
    }
}
void solve(){cin >> n;
    map<int, int> comp;
    rep(i, 1, n){
        cin >> from[i] >> to[i] >> gain[i];
        comp[from[i]] = 1, comp[to[i]] = 1;
    }
    compress(comp);
    rep(i, 1, 400004){
        dp[i] = dp[i - 1];
        for(auto [from, gain] : rev_proj[i]){
            dp[i] = max(dp[i], dp[from - 1] + gain);
        }
    }
    cout << dp[400004];
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}