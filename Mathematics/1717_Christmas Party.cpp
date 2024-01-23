#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define rep(i, st, n) for(int i = st; i < n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define pp pop()
#define tp top()
#define ph(x) push(x)
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define init = {0}
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;
const ll mod = 1e9+7;
ll fast_mul(ll x, ll p){
    ll ans = 0;
    while (x > 0){
        if (x & 1) ans = (ans + p) % mod;
        x >>= 1; p <<= 1;
    }
    return ans;
}
int main(){
    IO;
    int n; cin >> n;
    ll ans = 1;
    n--;
    while (n > 0){
        ans = fast_mul(ans, n);
        ans = fast_mul(ans, n);
        n >>= 1;
    }
    cout << ans;
}