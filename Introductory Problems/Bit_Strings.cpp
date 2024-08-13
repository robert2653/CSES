#include <bits/stdc++.h>
using namespace std;
using ll = long long;
const ll mod = 1e9 + 7;
ll fpow(ll x, ll y){
    x %= mod; y %= mod;
    ll ans = 1;
    while(y > 0){
        if(y & 1) ans = ans * x % mod;
        y >>= 1;
        x = x * x % mod;
    }
    return ans;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll n; cin >> n;
    cout << fpow(2, n);
}