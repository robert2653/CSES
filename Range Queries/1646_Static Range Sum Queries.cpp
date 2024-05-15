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
ll tree[4*maxn];
ll num[maxn];
ll ans;
void build(int L, int R, int now){
    if(L == R){
        tree[now] = num[L];
        return;
    }
    int M = (L + R) / 2;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now] = tree[lp] + tree[rp];
}
void query(int l, int r, int L, int R, int now){
    if(l <= L && R <= r){
        ans += tree[now];
        return;
    }
    int M = (L + R) / 2;
    if(r <= M){
        query(l, r, L, M, lp);
        return;
    }
    else if(l > M){
        query(l, r, M+1, R, rp);
        return;
    }
    else {
        query(l, r, L, M, lp);
        query(l, r, M+1, R, rp);
    }
}
int main(){
    IO;
    int n, q;  cin >> n >> q;
    rep(i, 1, n+1){
        cin >> num[i];
    }
    build(1, n, 1);
    rep(i, 1, q+1){
        int l, r; cin >> l >> r;
        ans = 0;
        query(l, r, 1, n, 1);
        cout << ans << endl; 
    }
    // rep(i, 1, 4*n+1){
    //     cout << i << ":" << tree[i] << endl;
    // }
}