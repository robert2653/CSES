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
    ll lazy_l, lazy_gap;
    ll sum = 0;
} Node;
const ll inf = 1LL << 62;
const int intf = INT_MAX;
const int maxn = 2e5+5;
Node tree[maxn*4];
int nums[maxn];
int n, q;
ll prefix[maxn];

void build(int L, int R, int now){
    if(L == R){
        tree[now].sum = nums[L];
        return;
    }
    int M = mid;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
}
void push(int now, int L, int R){
    int M = mid;
    if(L != R){
        tree[lp].lazy_l += tree[now].lazy_l; 
        tree[rp].lazy_l += tree[now].lazy_l + (M+1-L)*tree[now].lazy_gap;
        tree[lp].lazy_gap += tree[now].lazy_gap;
        tree[rp].lazy_gap += tree[now].lazy_gap;
    }
}
void apply_tag(int now, int L, int R){
    ll l = tree[now].lazy_l;
    ll r = l + (R-L) * tree[now].lazy_gap;
    tree[now].sum += (l + r)*(R-L+1)/2;
	if(L != R){
        push(now, L, R);
    }
	tree[now].lazy_gap = tree[now].lazy_l = 0;
}
void modify(int l, int r, int L, int R, int now){
    if(R < l || r < L || L > n)
        return;
    if(l <= L && R <= r){
        tree[now].lazy_l += L-l+1;
        tree[now].lazy_gap ++;
        return;
    }
    apply_tag(now, L, R);	// 清乾淨
    int M = mid;
    modify(l, r, L, M, lp);
    modify(l, r, M+1, R, rp);
    apply_tag(lp, L, M);
    apply_tag(rp, M+1, R);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
}
ll query(int l, int r, int L, int R, int now){
    if(R < l || r < L || L > n){
        return 0;
    }
    apply_tag(now, L, R);
    if(l <= L && R <= r){
        return tree[now].sum;
    }
    int M = mid;
	return query(l, r, L, M, lp) + query(l, r, M+1, R, rp);
}
void solve(){
    cin >> n >> q;
    rep(i, 1, n){
        cin >> nums[i];
        prefix[i] = prefix[i-1] + i;
    }
    build(1, n, 1);
    rep(i, 1, q){
        int op; cin >> op;
        if(op == 1){
            int l, r; cin >> l >> r;
            modify(l, r, 1, n, 1);
        }
        else {
            int l, r; cin >> l >> r;
            cout << query(l, r, 1, n, 1) << endl;
        }
    }
}
int main(){
    IO;
    solve();
}