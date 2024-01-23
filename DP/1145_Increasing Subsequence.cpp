// classic LIS
// 1 2 4 5 3 6 -> 1 2 3 5 6 // lower_bound 不影響結果
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
    int n; cin >> n;
    vector<int> v(n);
    lrep(i, 0, n){
        cin >> v[i];
    }
    int dp[n]; vector<int> mono;
    mono.push_back(v[0]);
    dp[0] = 1;  int L = 1;
    lrep(i, 1, n){
        if(v[i] > mono.back()){
            mono.push_back(v[i]);
            dp[i] = ++L;
        }
        else {
            auto it = lower_bound(all(mono), v[i]);
            *it = v[i];
            dp[i] = it - mono.begin() + 1;
        }
    }
    vector<int> ans;
    cout << L << endl;
    // for(int i = n - 1; i >= 0; i--){
    //     if(dp[i] == L){
    //         ans.push_back(v[i]);
    //         L--;
    //     }
    // }
    // reverse(all(ans));
    // for(auto i : ans){
    //     cout << i << " ";
    // }
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}