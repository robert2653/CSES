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
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
vector<ll> Hash(string s, ll b, ll p){
    vector<ll> ans = {0};
    for(auto c: s){
        ans.push_back((ans.back() * b + (c-'a'+1)) % p);
    }
    return ans;
}
ll query(vector<ll> &vec, vector<ll> &pow, ll l, ll r, ll p){
    ll length = r - l + 1;
    return (vec[r+1] - vec[l] * pow[length] % p + p) % p;
}
void solve(){
    string s, q; cin >> s >> q;
    ll mod = 1e9+7, b = 30;
    // 012 01
    vector<ll> v = Hash(q, b, mod);
    ll find = v.back();
    ll ans = 0;
    vector<ll> pow; pow.push_back(1);
    rep(i, 1, 1000005){
        pow.push_back(pow.back() * b % mod);
    }
    vector<ll> hash = Hash(s, b, mod);
    ll s_size = s.sz, q_size = q.sz;
    for(ll l = 0, r = q_size-1; r < s_size; l++, r++){
        ll tmp = query(hash, pow, l, r, mod);
        if (tmp == find) ans++;
    }
    cout << ans;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}