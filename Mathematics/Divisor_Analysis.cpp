#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1E9 + 7;
ll fast_pow(ll x, ll p, ll MOD) {
    ll ans = 1;
    x %= MOD, p %= MOD;
    while (p > 0) {
        if (p & 1) {
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
    for (int i = 0; i < n; i++) {
        cin >> v[i].first >> v[i].second;
        if (v[i].second & 1) {
            all_even = 0;
        }
    }
    ll num = 1;
    ll sum = 1;
    ll prod = 1;
    ll pow = 1;
    bool done = 1;
    if (!all_even) done = 0;
    for (int i = 0; i < v.size(); i++) {
        auto &[x, y] = v[i];
        num = num * (y + 1) % mod;
        ll tmp = ((fast_pow(x, y + 1, mod) - 1 + mod) % mod * fast_pow(x - 1, mod - 2, mod)) % mod;
        sum = sum * tmp % mod;
        if (!done && (y & 1)) {
            pow = pow * (y + 1) / 2 % (mod - 1);
            done = 1;
        } else {
            pow = pow * (y + 1) % (mod - 1);
        }
        if (all_even) {
            prod = prod * fast_pow(x, y / 2, mod) % mod;
        } else {
            prod = prod * fast_pow(x, y, mod) % mod;
        }
    }
    // if(all_even)
    prod = fast_pow(prod, pow, mod);
    // 2^2 3^2
    // 1, 2, 3, 4, 6, 9, 12, 18, 36
    // else prod = fast_pow(prod, fast_mul(pow, fast_pow(2, mod - 3, mod - 1), mod - 1), mod);
    cout << num << " " << sum << " " << prod << " ";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    solve();
}