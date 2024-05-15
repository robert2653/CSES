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
    ll val;
    ll add;
    ll sum;
} Node;
const ll inf = 1LL << 62;
const int intf = INT_MAX;
const int maxn = 2e5+5;
Node tree[maxn*4];
int nums[maxn];
int n, q;

void push(int now, int child){
    if(tree[now].val){
        tree[child].val = tree[now].val;
        tree[child].add = tree[now].add;
    }
    else {
        tree[child].add += tree[now].add;
    }
}
void apply_tag(int now, int L, int R){
    if(tree[now].val)
        tree[now].sum = (R-L+1)*tree[now].val;
    tree[now].sum += (R-L+1)*tree[now].add;
    if(L != R){
        push(now, lp);
        push(now, rp);
    }
    tree[now].add = tree[now].val = 0;
}
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
void modify_add(int l, int r, int L, int R, int now, int add){
    if(R < l || r < L)
        return;
    if(l <= L && R <= r){
        tree[now].add += add;	// 到底了，加好不丟了
        return;
    }
    apply_tag(now, L, R);	// 丟下去
    int M = mid;
    modify_add(l, r, L, M, lp, add);	// 走下來
    modify_add(l, r, M+1, R, rp, add);	// 走下來
    apply_tag(lp, L, M);	// 算好(最底的也會，順便丟下去)
    apply_tag(rp, M+1, R);	// 算好(最底的也會，順便丟下去)
    tree[now].sum = tree[lp].sum + tree[rp].sum;	// 加上去
}
void modify_mod(int l, int r, int L, int R, int now, int mod){
    if(R < l || r < L)
        return;
    if(l <= L && R <= r){
		tree[now].val = mod;
		tree[now].add = 0;
        return;
    }
    apply_tag(now, L, R);
    int M = mid;
    modify_mod(l, r, L, M, lp, mod);
    modify_mod(l, r, M+1, R, rp, mod);
    apply_tag(lp, L, M);
    apply_tag(rp, M+1, R);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
}
ll query(int l, int r, int L, int R, int now){
    int M = mid;
    // if(l <= L && R <= r){
    //     apply_tag(now, L, R);
    //     return tree[now].sum;
    // }
    // if(r <= M){
    //     apply_tag(now, L, R);
    //     return query(l, r, L, M, lp);
    // }
    // else if(M < l){
    //     apply_tag(now, L, R);
    //     return query(l, r, M+1, R, rp);
    // }
    // else {
    //     apply_tag(now, L, R);
    //     return query(l, r, L, M, lp) + query(l, r, M+1, R, rp);
    // }
    if(R < l || r < L || L > n){
        return 0;
    }
    apply_tag(now, L, R);
    if(l <= L && R <= r){
        return tree[now].sum;
    }
	return query(l, r, L, M, lp) + query(l, r, M+1, R, rp);
}
void solve(){
    cin >> n >> q;
    rep(i, 1, n){
        cin >> nums[i];
    }
    init(tree);
    build(1, n, 1);
    rep(i, 1, q){
        int op; cin >> op;
        if(op == 1){
            int l, r, add; cin >> l >> r >> add;
            modify_add(l, r, 1, n, 1, add);
        }
        else if(op == 2){
            int l, r, mod; cin >> l >> r >> mod;
            modify_mod(l, r, 1, n, 1, mod);
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
// void modify_add(int l, int r, int L, int R, int now, int add){
//     if(l <= L && R <= r){
//         tree[now].add += add;
//         return;
//     }
//     int M = mid;
//     if(r <= M){
//         apply_tag(now, L, R);
//         modify_add(l, r, L, M, lp, add);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     else if(l > M){
//         apply_tag(now, L, R);
//         modify_add(l, r, M+1, R, rp, add);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     else {
//         apply_tag(now, L, R);
//         modify_add(l, r, L, M, lp, add);
//         modify_add(l, r, M+1, R, rp, add);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     tree[now].sum = tree[lp].sum + tree[rp].sum;
// }

// void modify_mod(int l, int r, int L, int R, int now, int mod){
//     if(l <= L && R <= r){
//         tree[now].set_val = 1;
//         tree[now].val = mod;
//         tree[now].add = 0;
//         return;
//     }
//     int M = mid;
//     if(r <= M){
//         apply_tag(now, L, R);
//         modify_mod(l, r, L, M, lp, mod);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     else if(l > M){
//         apply_tag(now, L, R);
//         modify_mod(l, r, M+1, R, rp, mod);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     else{
//         apply_tag(now, L, R);
//         modify_mod(l, r, L, M, lp, mod);
//         modify_mod(l, r, M+1, R, rp, mod);
//         apply_tag(lp, L, M);
//         apply_tag(rp, M+1, R);
//     }
//     tree[now].sum = tree[lp].sum + tree[rp].sum;
// }