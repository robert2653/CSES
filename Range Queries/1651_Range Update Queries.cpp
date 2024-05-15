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

int n, q;
ll nums[maxn];
ll mod[4*maxn];
ll d;
void modify(int l, int r, int L, int R, int now, int add){
    if(l <= L && R <= r){
        mod[now] += add;
        return;
    }
    int M = (L+R) / 2;
    if(r <= M){
        modify(l, r, L, M, lp, add);
    }
    else if(M < l){
        modify(l, r, M+1, R, rp, add);
    }
    else {
        modify(l, r, L, M, lp, add);
        modify(l, r, M+1, R, rp, add);
    }
}
void query(int pos, int L, int R, int now){
    if(L == R){
        d += mod[now];
        return;
    }
    int M = (L+R) / 2;
    if(L <= pos && pos <= R) d += mod[now];
    if(pos <= M){
        query(pos, L, M, lp);
    }
    else if(M < pos){
        query(pos, M+1, R, rp);
    }
    else {
        query(pos, L, M, lp);
        query(pos, M+1, R, rp);
    }
}
void solve(){
    cin >> n >> q;
    rep(i, 1, n+1){
        cin >> nums[i];
    }
    rep(i, 1, q+1){
        int op; cin >> op;
        if(op == 1){
            int l, r, add; cin >> l >> r >> add;
            modify(l, r, 1, n, 1, add);
        }
        else {
            int pos; cin >> pos;
            d = 0;
            query(pos, 1, n, 1);
            cout << nums[pos] + d << endl;
        }
    }
    // rep(i, 1, 4*n+1){
    //     cout << i << ":" << mod[i] << endl;
    // }
}
int main(){
    IO;
    solve();
}
