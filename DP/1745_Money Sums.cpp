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
bool dp[100001];
void solve(){
    init(dp, 0);
    dp[0] = 1;
    int n; cin >> n;
    vector<ll> coin(n+1);
    int sum = 0;
    rep(i, 1, n){
        cin >> coin[i];
        sum += coin[i];
    }
    rep(i, 1, n){
        for(int j = sum; j >= 0; j--){
            if(dp[j]){
                if(j + coin[i] <= sum){
                    dp[j + coin[i]] = 1;
                }
            }
        }
    }
    vector<int> ans;
    rep(i, 1, sum){
        if(dp[i]) ans.push_back(i);
    }
    cout << ans.sz << endl;
    for(auto &i : ans) cout << i << " ";
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}