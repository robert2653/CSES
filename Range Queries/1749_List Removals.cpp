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
int nums[maxn];
int tree[maxn*4];
bool used[maxn];
int mod;
void query(int pos, int L, int R, int now){
    if(L == R){
        mod += tree[now];
        return;
    }
    int M = (L+R) / 2;
    if(L <= pos && pos <= R){
        mod += tree[now];
    }
    if(pos <= M){
        query(pos, L, M, lp);
    }
    else {
        query(pos, M+1, R, rp);
    }
}
void modify(int l, int r, int L, int R, int now){
    if(l <= L && R <= r){
        tree[now]++;
        return;
    }
    int M = (L+R) / 2;
    if(r <= M){
        modify(l, r, L, M, lp);
    }
    else if(M < l){
        modify(l, r, M+1, R, rp);
    }
    else {
        modify(l, r, L, M, lp);
        modify(l, r, M+1, R, rp);
    }
}
bool check(int pos, int fin){
    mod = 0;
    query(pos, 1, n, 1);
    if(pos - mod >= fin) return true;
    else return false;
}
int binary(int fin){    // 在ans前有query(ans)被選過，而ans-mod == pos
    int L = -1, R = n;
    while(L <= R){
        int M = (L+R) / 2;
        if(check(M, fin)){
            R = M-1;
        }
        else L = M+1;
    }
    return L;
}
void solve(){
    cin >> n;
    init(used);
    rep(i, 1, n+1){
        cin >> nums[i];
    }
    rep(i, 1, n+1){
        int pos; cin >> pos;
        int ans = binary(pos);
        cout << nums[ans] << endl;
        modify(ans, n, 1, n, 1);
        // rep(j, q, 4*n){
        //     cout << j << ":" << tree[j] << endl;
        // }
    }
}
int main(){
    IO;
    solve();
}