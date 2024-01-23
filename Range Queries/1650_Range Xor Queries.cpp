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

ll dp[maxn];
void solve(){
    int n, q; cin >> n >> q;
    dp[0] = 0;
    rep(i, 1, n+1){
        cin >> dp[i];
        dp[i] ^= dp[i-1];
    }
    rep(i, 1, q+1){
        int l, r; cin >> l >> r;
        cout << (dp[r]^dp[l-1]) << endl;
    }
}
int main(){
    IO;
    solve();
}