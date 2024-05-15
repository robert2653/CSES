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

ll nums[maxn];
ll tree[maxn*4];
void build(int L, int R, int now){
    if(L==R){
        tree[now] = nums[L];
        return;
    }
    int M = (L+R) / 2;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now] = min(tree[lp], tree[rp]);
}
void modify(int pos, int L, int R, int now){
    if(L==R){
        tree[now] = nums[L];
        return;
    }
    int M = (L+R) / 2;
    if(pos <= M) modify(pos, L, M, lp);
    else modify(pos, M+1, R, rp);
    tree[now] = min(tree[lp], tree[rp]);
}
ll query(int l, int r, int L, int R, int now){
    if(l <= L && R <= r){
        return tree[now];
    }
    int M = (L+R) / 2;
    if(r <= M){
        return query(l, r, L, M, lp);
    }
    else if(M < l){
        return query(l, r, M+1, R, rp);
    }
    else {
        return min(query(l, r, L, M, lp), query(l, r, M+1, R, rp));
    }
}
void solve(){
    int n, q; cin >> n >> q;
    rep(i, 1, n+1){
        cin >> nums[i];
    }
    build(1, n, 1);
    rep(i, 1, q+1){
        int op; cin >> op;
        if(op == 1){
            int pos, val; cin >> pos >> val;
            nums[pos] = val;
            modify(pos, 1, n, 1);
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