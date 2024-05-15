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
#define mid (L+R)/2
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

typedef struct {
    ll sum, prefix, suffix, middle_max;
} Node;
int nums[maxn];
Node tree[maxn*4];
void build(int L, int R, int now){
    if(L == R){
        tree[now].sum = nums[L];
        tree[now].prefix = tree[now].suffix = (nums[L] > 0 ? nums[L] : 0);
        return;
    }
    int M = mid;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
    tree[now].prefix = max(tree[lp].sum+tree[rp].prefix, tree[lp].prefix);
    tree[now].suffix = max(tree[lp].suffix+tree[rp].sum, tree[rp].suffix);
    tree[now].middle_max = max(max(tree[lp].middle_max, tree[rp].middle_max), tree[lp].suffix+tree[rp].prefix);
    tree[now].middle_max = max(max(tree[now].middle_max, tree[now].prefix), tree[now].suffix);
}
void modify(int pos, int val, int L, int R, int now){
    if(L == R){
        tree[now].sum = val;
        tree[now].prefix = tree[now].suffix = (val > 0 ? val : 0);
        return;
    }
    int M = mid;
    if(pos <= mid) modify(pos, val, L, M, lp);
    else modify(pos, val, M+1, R, rp);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
    tree[now].prefix = max(tree[lp].sum+tree[rp].prefix, tree[lp].prefix);
    tree[now].suffix = max(tree[lp].suffix+tree[rp].sum, tree[rp].suffix);
    tree[now].middle_max = max(max(tree[lp].middle_max, tree[rp].middle_max), tree[lp].suffix+tree[rp].prefix);
    tree[now].middle_max = max(max(tree[now].middle_max, tree[now].prefix), tree[now].suffix);
}
void solve(){
    int n, q; cin >> n >> q;
    rep(i, 1, n+1) cin >> nums[i];
    build(1, n, 1);
    rep(i, 1, q+1){
        int pos, val; cin >> pos >> val;
        modify(pos, val, 1, n, 1);
        // cout << q1.max_pref - (q2.min_pref > 0 ? 0 : q2.min_pref) << endl;
        cout << tree[1].middle_max << endl;
    }
}// -4 -2 -1 -7 3 3 -6 -8 -9 9
// 9 2 -3 10 1 3 6 9 0 -8
// 9 10-3 10 1 3 6 9 0 -8
// 9 10-3 10 1 3-3 9 0 -8
// 9 10-3 10 1-6-3 9 0 -8
// 9 10-3 10 1-6-3 1 0 -8
// 1 10-3 10 1-6-3 1 0 -8
// 1 10-3 10 1 7-3 1 0 -8
// 1 10-3 10 1 7-3-100 -8
// 1 10-7 10 1 7-3-100 -8
// 1 -9-7 10 1 7-3-100 -8
int main(){
    IO;
    solve();
}