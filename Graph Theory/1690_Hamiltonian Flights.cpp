// Bit_Mask_DP, Travel Exactly Once
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
#define init(x, k) lrep(i, 0, sizeof(x)/sizeof(x[0])){x[i] = k;}
#define vec_init(x, k) lrep(i, 0, x.sz){x[i] = k;}
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
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
int dp[(1<<20)-1][20];
vector<int> rev_adj[20];
int n, m;
const int mod = 1e9 + 7;
void solve(){
    cin >> n >> m;
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        rev_adj[--v].push_back(--u);
    }
    dp[1][0] = 1;
    lrep(road, 1 << 1, 1 << n){
        // 如果路徑沒有1
        if(road & 1 == 0) continue;
        // 包含終點但沒全走過
        if(road & (1 << (n - 1)) && road != ((1 << n) - 1)) continue;
        // dp
        for (int end = 0; end < n; end++) {
            // 當前路徑不包含end
			if ((road & (1 << end)) == 0) continue;
            // 去掉結束點就是前個點
			int pre_road = road - (1 << end);
			for (int pre_road_end : rev_adj[end]) {
                // j 是 prev的終點
				if ((road & (1 << pre_road_end))) {
					dp[road][end] += dp[pre_road][pre_road_end];
					dp[road][end] %= mod;
				}
			}
		}
    }
    cout << dp[(1 << n) - 1][n - 1];
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}