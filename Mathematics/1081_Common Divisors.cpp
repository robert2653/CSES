// 線篩+DP
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
#define init(x, k) memset(x, k, sizeof(x));
#define vec_init(x, k) x.assign(x.size(), k);
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
const ll llinf = 1e18;
const int inf = 1e9;
const int MOD = 1e9+7;
const int maxn = 1e6+5;
// 數量 = (x+1)(y+1)(z+1)...
// 總和 = (a^0+a^1...+a^x)(b^0+...+b^y)
// 乘積 = N(x+1)(y+1)(z+1)/2
int appear[maxn];
void solve(){
    int q; cin >> q;
    init(appear, 0);
    rep(i, 1, q){
        int tmp; cin >> tmp;
        appear[tmp]++;
    }
    for(int i = 1000000; i >= 1; i--){
        if(appear[i] >= 2){
            cout << i;
            return;
        }
        int cnt = 0;
        for(int j = i; j <= 1000000; j += i){
            cnt += appear[j];
        }
        if(cnt >= 2){
            cout << i;
            return;
        }

    }
}
int main(){
    IO;
    int t = 1;
    // rep(i, 1, 1000000) Is_Prime[i][0] = 1;
    // Is_Prime[1][0] = 0;
    // rep(i, 2, 1000){
    //     if(Is_Prime[i][0]){
    //         for(int j = i + i; j <= 1000000; j += i){
    //             Is_Prime[j][0] = 0;
    //             Is_Prime[j][1] = i;
    //         }
    //     }
    // }
    // cin >> t;
    while(t--){
        solve();
    }
}