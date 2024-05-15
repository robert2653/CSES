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
int bucket[10000005];
int tree[40000020];
map<int, int> brute;
int ans;
vector<int> sal(maxn);
int bucket_no(int val){
    if(!(val%100)) val--;
    return (val/100+1);
}
void build(int L, int R, int now){
    if(L == R){
        tree[now] = bucket[L];
        return;
    }
    int M = (L+R) / 2;
    build(L, M, lp);
    build(M+1, R, rp);
    tree[now] = tree[lp] + tree[rp];
}
void query(int l, int r, int L, int R, int now){
    if(l <= L && R <= r){
        ans += tree[now];
        return;
    }
    int M = (L+R) / 2;
    if(r <= M){
        query(l, r, L, M, lp);
    }
        
    else if(M < l){
        query(l, r, M+1, R, rp);
    }
    else {
        query(l, r, L, M, lp);
        query(l, r, M+1, R, rp);
    }
}
void modify(int pos, int L, int R, int now){
    if(L == R){
        tree[now] = bucket[L];
        return;
    }
    int M = (L+R) / 2;
    if(pos <= M) modify(pos, L, M, lp);
    else modify(pos, M+1, R, rp);
    tree[now] = tree[lp] + tree[rp];
}
void solve(){
    init(tree);
    init(bucket);
    rep(i, 1, n+1){
        int tmp; cin >> tmp;
        bucket[bucket_no(tmp)]++; // 1~100, 101~200, 201~300
        brute[tmp]++;             //  1       2       3
        sal[i] = tmp;
    }
    build(1, 10000000, 1);
    rep(i, 1, q+1){
        char op; cin >> op;
        if(op == '!'){
            int pos, val; cin >> pos >> val;
            int ori = sal[pos];
            sal[pos] = val;
            brute[ori]--; brute[val]++;
            bucket[bucket_no(ori)]--;
            bucket[bucket_no(val)]++;
            modify(bucket_no(ori), 1, 10000000, 1);
            modify(bucket_no(val), 1, 10000000, 1);
        }
        else {
            ans = 0;
            int l, r; cin >> l >> r;
            int lno = bucket_no(l)+1, rno = bucket_no(r)-1;
            if(lno <= rno){
                query(lno, rno, 1, 10000000, 1);
                auto it = brute.lower_bound(l);
                while(it != brute.end() && it->first <= (lno-1)*100){
                    ans += it->second;
                    it++;
                }
                it = brute.lower_bound(rno*100+1);
                while(it != brute.end() && it->first <= r){
                    ans += it->second;
                    it++;
                }
            }
            else {
                auto it = brute.lower_bound(l);
                while(it != brute.end() && it->first <= r){
                    ans += it->second;
                    it++;
                }
            }
            cout << ans << endl;
        }
    }
}
int main(){
    IO;
    cin >> n >> q;
    solve();
}