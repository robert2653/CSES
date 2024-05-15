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
#define init(x) memset(x, 0, sizeof(x));
#define lp 2*now
#define rp 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll inf = LLONG_MAX;
const int intf = INT_MAX;
const int maxn = 1e3+5;
vector<vector<int>> floo(maxn, vector<int>(maxn, 1));
int n, m; 
void dfs(int i, int j){
    if(!floo[i-1][j]){
        floo[i-1][j] = 1;
        dfs(i-1, j);
    }
    if(!floo[i+1][j]){
        floo[i+1][j] = 1;
        dfs(i+1, j);
    }
    if(!floo[i][j-1]){
        floo[i][j-1] = 1;
        dfs(i, j-1);
    }
    if(!floo[i][j+1]){
        floo[i][j+1] = 1;
        dfs(i, j+1);
    }
}
void solve(){
    cin >> n >> m;
    int ans = 0;
    rep(i, 1, n){
        rep(j, 1, m){
            char r; cin >> r;
            if(r == '.'){
                floo[i][j] = 0;
            }
            else floo[i][j] = 1;
        }
    }
    rep(i, 1, n){
        rep(j, 1, m){
            if(!floo[i][j]){
                ans++;
                floo[i][j] = 1;
                dfs(i, j);
            }
        }
    }
    cout << ans;
}
int main(){
    IO;
    solve();
}