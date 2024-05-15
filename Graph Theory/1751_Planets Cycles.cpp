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

int nextnode[maxn];
int n;
bool vis[maxn];
int ans[maxn];
int no[maxn];
vector<vector<int>> cycles;
void find_cycle(int now){
    unordered_set<int> appear;
    vector<int> vec;
    bool found_cycle = 1;
    while(appear.find(now) == appear.end()){
        appear.insert(now);
        vec.push_back(now);
        if(vis[now]){   // 沒找到環
            found_cycle = false;
            break;
        }
        now = nextnode[now];
    }
    for(auto &i : vec) vis[i] = true;
    if(!found_cycle){
        return;
    }
    int start = find(all(vec), now) - vec.begin();  // cycle的起點
    int end = vec.size();
    vector<int> cycle;
    lrep(i, start, end){
        cycle.push_back(vec[i]);
    }
    cycles.push_back(cycle);
}
void find_outside(int now, unordered_set<int> &done){
    if(done.find(now) != done.end()){   // 碰到環了
        return;
    }
    find_outside(nextnode[now], done);
    done.insert(now);
    // no[now] = no[nextnode[now]] - 1;
    ans[now] = ans[nextnode[now]] + 1;
}
void solve(){
    // freopen("test_input.txt", "r", stdin);
    cin >> n;
    rep(i, 1, n){
        cin >> nextnode[i];
    }
    rep(i, 1, n){
        if(!vis[i])
            find_cycle(i);
    }
    unordered_set<int> done;
    int cyc_idx = 0;
    for(auto cycle : cycles){
        int cyc_no = 0;
        for(auto &j : cycle){
            done.insert(j);
            no[j] = cyc_no++;
            ans[j] = cycle.size();
        }
        cyc_idx++;
    }
    rep(i, 1, n){
        find_outside(i, done);
    }
    rep(i, 1, n){
        cout << ans[i] << endl;
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