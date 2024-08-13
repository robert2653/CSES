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
const int maxn = 2e5+5;

int n, m;
int boss[maxn];
int set_sz[maxn];
void _init(int n){
    for(int i = 1; i <= n; ++i){
        set_sz[i] = 1;  //每個群體的大小是1
        boss[i] = i;    //每個人的boss是自己
    }
}
int find_boss(int x){
    if(boss[x] != x){
        boss[x] = find_boss(boss[x]);
    }
    return boss[x];
}
void uni(int u, int v){
    int boss_u = find_boss(u);
    int boss_v = find_boss(v);
    if(boss_u == boss_v) return;
    if(set_sz[boss_u] > set_sz[boss_v]) swap(boss_u, boss_v);
    boss[boss_u] = boss_v;  //x群的boss接到y上
    set_sz[boss_v] += set_sz[boss_u];   //x群合併到y群
}
void solve(){
    cin >> n >> m;
    _init(n);
    rep(i, 1, m){
        int u, v; cin >> u >> v;
        uni(u, v);
    }
    set<int> ans;
    rep(i, 1, n){
        ans.insert(find_boss(i));
    }
    cout << ans.size()-1 << endl;
    auto it = ans.begin();
    while(it != ans.end()){
        int u = *it;
        it++; if(it == ans.end()) break;
        cout << u << " " << *it << endl;
    }
}
int main(){
    IO;
    solve();
}