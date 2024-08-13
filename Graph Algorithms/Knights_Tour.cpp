// 暴搜
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
int n, n_pin;
int ans[9][9];
int f_row[] = {2, 2, -2, -2, 1, 1, -1, -1};
int f_col[] = {1, -1, 1, -1, 2, -2, 2, -2};
// J.C. Warnsdorff 在 1823 年提出，將最難的位置走完，接下來的路就寬廣了
// 騎士要走的下一步，「為下一步再選擇時，能走的步數最少的一步」
// 使用這個方法，有較高的機率找出走法。
void print(){
    lrep(i, 0, 8){
        lrep(j, 0, 8){
            cout << ans[i][j] << " ";
        }
        cout << endl;
    }
}
int nxt_node_prob(int row, int col){
    int prob = 0;
    lrep(i, 0, 8){
        int nxt_row = row + f_row[i], nxt_col = col + f_col[i];
        if(nxt_row >= 0 && nxt_row < n && nxt_col >= 0 && nxt_col < n && ans[nxt_row][nxt_col] == 0){
            prob++;
        }
    }
    return prob;
}
bool brute(int now, int row, int col){
    ans[row][col] = now;
    if(now == n_pin){
        print();
        return 1;
    }
    vector<pair<int, pii>> p;
    lrep(i, 0, 8){
        int nxt_row = row + f_row[i], nxt_col = col + f_col[i];
        if(nxt_row >= 0 && nxt_row < n && nxt_col >= 0 && nxt_col < n && ans[nxt_row][nxt_col] == 0){
            p.push_back({nxt_node_prob(nxt_row, nxt_col), {nxt_row, nxt_col}});
        }
    }
    sort(all(p));
    for (auto nxt : p){
        if (brute(now + 1, nxt.second.first, nxt.second.second)) return 1;
    }
    ans[row][col] = 0;
    return 0;
}
void solve(){
    n = 8; n_pin = n * n;
    lrep(i, 0, n){
        lrep(j, 0, n){
            ans[i][j] = 0;
        }
    }
    int x, y; cin >> x >> y;    // col, row;
    bool useless = brute(1, y - 1, x - 1);
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}