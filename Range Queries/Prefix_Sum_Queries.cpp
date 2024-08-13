// maxpre(now) = max (maxpre(lp), sum(lp)+maxpre(rp)); 
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
    ll sum, pref;
} Node;
Node tree[maxn*4];
int nums[maxn];
ll ans;
void build(int L, int R, int now){
    if(L == R){
        // tree[now].sum = tree[now].pref = nums[L];
        tree[now].sum = nums[L];
        tree[now].pref = nums[L];
        return;
    }
    int M = mid;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
    tree[now].pref = max(tree[lp].pref, tree[lp].sum+tree[rp].pref);
}
void modify(int pos, int val, int L, int R, int now){
    if(L == R){
        // tree[now].sum = tree[now].pref = nums[L];
        tree[now].sum = val;
        tree[now].pref = val;
        return;
    }
    int M = mid;
    if(pos <= M) modify(pos, val, L, M, lp);
    else modify(pos, val, M+1, R, rp);
    tree[now].sum = tree[lp].sum + tree[rp].sum;
    tree[now].pref = max(tree[lp].pref, tree[lp].sum+tree[rp].pref);
}
Node query(int l, int r, int L, int R, int now){    // query也要dp
    if(l <= L && R <= r){
        return tree[now];
    }
    int M = mid;
    if(r <= M){
        return query(l, r, L, M, lp);
    }
    else if(M < l){
        return query(l, r, M+1, R, rp);
    }
    else {
        Node q1 = query(l, r, L, M, lp);
        Node q2 = query(l, r, M+1, R, rp);
        return {q1.sum+q2.sum, max(q1.pref, q1.sum+q2.pref)};
    }
}
void solve(){
    int n, q; cin >> n >> q;
    rep(i, 1, n+1){
        int tmp; cin >> tmp;
        nums[i] = tmp;
    }
    build(1, n, 1);
    rep(i, 1, q+1){
        int op; cin >> op;
        if(op == 1){    // change
            int pos, val; cin >> pos >> val;
            modify(pos, val, 1, n, 1);
        }
        else {  // query
            int l, r; cin >> l >> r;
            Node ans = query(l, r, 1, n, 1);
            cout << (ans.pref < 0 ? 0 : ans.pref) << endl;
        }
    }

}
int main(){
    IO;
    solve();
}