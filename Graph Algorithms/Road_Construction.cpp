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
int ans, mx_sz = 1;
int boss[maxn];
int set_sz[maxn];
int find_boss(int x){
    if(boss[x] == x) return x;
    return boss[x] = find_boss(boss[x]);
}
void dsu(int x, int y){
    int boss_x = find_boss(x);
    int boss_y = find_boss(y);
    if(boss_x != boss_y){
        ans--;
        if(set_sz[boss_x] < set_sz[boss_y]){
            swap(boss_x, boss_y);
        }
        boss[boss_y] = boss_x;
        set_sz[boss_x] += set_sz[boss_y];
        mx_sz = max(mx_sz, set_sz[boss_x]);
    }
    cout << ans << " " << mx_sz << endl;
}
void solve(){
    int n, q; cin >> n >> q;
    ans = n;
    rep(i, 1, n){
        boss[i] = i;
        set_sz[i] = 1;
    }
    rep(i, 1, q){
        int x, y;
        cin >> x >> y;
        dsu(x, y);
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