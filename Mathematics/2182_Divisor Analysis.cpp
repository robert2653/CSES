#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9+7;
ll fast_mul(ll x, ll y, ll MOD){
    ll ans = 0;
    x %= MOD, y %= MOD;
    while(y > 0){
        if(y & 1){
            (ans += x) %= MOD;
        }
        (x <<= 1) %= MOD;
        y >>= 1;
    }
    return ans;
}
ll fast_pow(ll x, ll p, ll MOD){
    ll ans = 1;
    x %= MOD, p %= MOD;
    while(p > 0){
        if(p & 1){
            (ans *= x) %= MOD;
        }
        (x *= x) %= MOD;
        p >>= 1;
    }
    return ans;
}
void solve(){
    ll n; cin >> n;
    vector<pair<ll, ll>> v(n);
    bool all_even = 1;
    for(int i = 0; i < n; i++){
        cin >> v[i].first >> v[i].second;
        if(v[i].second & 1){
            all_even = 0;
        }
    }
    ll num = 1;
    ll sum = 1;
    ll pro = 1;
    ll pro_num = 1;
    bool done = 1;
    if(!all_even) done = 0;
    for(int i = 0; i < v.size(); i++){
        auto &[x, y] = v[i];
        num = fast_mul(num, y + 1, mod);
        // (a^(n+1)) / (n-1);
        ll tmp = y == 1 ? 1 + x : fast_mul(fast_pow(x, y + 1, mod) - 1, fast_pow(x - 1, mod - 2, mod), mod);
        sum = fast_mul(sum, tmp, mod);
        if(!done && (y & 1)){
            pro_num = fast_mul(pro_num, (y + 1) / 2, mod - 1);
            done = 1;
        }
        else pro_num = fast_mul(pro_num, y + 1, mod - 1);
        if(all_even){
            pro = fast_mul(pro, fast_pow(x, y / 2, mod), mod);
        }
        else {
            pro = fast_mul(pro, fast_pow(x, y, mod), mod);
        }
    }
    // if(all_even)
    pro = fast_pow(pro, pro_num, mod);
    // 2^2 3^2
    // 1, 2, 3, 4, 6, 9, 12, 18, 36
    // else pro = fast_pow(pro, fast_mul(pro_num, fast_pow(2, mod - 3, mod - 1), mod - 1), mod);
    cout << num << " " << sum << " " << pro << " ";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    solve();
}