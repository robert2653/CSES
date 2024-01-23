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
// ll dp[maxn];
ll dp[maxn];
char laby[maxn];
vi graph[maxn];
int in[maxn] = {0};
void solve(){
    // -1 +1 -n +n
    init(dp, 0);
    int n; cin >> n;
    int size = n * n;
    lrep(i, 0, n){
        lrep(j, 0, n){
            cin >> laby[i * n + j];
            if(j + 1 < n){
                graph[i * n + j].push_back(i * n + j + 1);
                in[i * n + j + 1]++;
            }
            if(i * n + j + n < size){
                graph[i * n + j].push_back(i * n + j + n);
                in[i * n + j + n]++;
            }
        }
    }
    if(laby[0] == '*'){
        cout << 0;
        return;
    }
    queue<int> q;
    q.push(0);
    dp[0] = 1;
    while(!q.empty()){
        int now = q.front(); q.pop();
        for(auto &nxt : graph[now]){
            in[nxt]--;
            if(laby[nxt] != '*'){
                (dp[nxt] += dp[now]) %= MOD;
            }
            if(in[nxt] == 0) q.push(nxt);
        }
    }
    cout << dp[size - 1];

}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}