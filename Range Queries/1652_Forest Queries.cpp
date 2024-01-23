#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define rep(i, st, n) for(int i = st; i < n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define init(x) memset(x, 0, sizeof(x));
#define lp 2*now
#define rp 2*now+1
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;
const int intf = INT_MAX;
const int maxn = 2e5+5;
int n, q; 
int dp[1005][1005];
void solve(){
    memset(dp, 0, sizeof(dp));
    cin >> n >> q;
    rep(i, 1, n+1){
        rep(j, 1, n+1){
            char tree; cin >> tree;
            dp[i][j] = dp[i][j-1];
            if(tree == '*'){
                dp[i][j]++;
            }
        }
        rep(j, 1, n+1){
            dp[i][j] += dp[i-1][j];
        }
    }
    rep(i, 1, q+1){
        int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
        cout << dp[y2][x2] - dp[y2][x1-1] - dp[y1-1][x2] + dp[y1-1][x1-1] << endl;
    }
}
int main(){
    IO;
    solve();
    // rep(i, 1, n+1){
    //     rep(j, 1, n+1) cout << dp[i][j] << " ";
    //     cout << endl;
    // }
}