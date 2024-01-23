#include <bits/stdc++.h>
using namespace std;
using ll = long long;
bool overflow(ll x, ll y, ll n){
    if(n / x < y) return true;
    return false;
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    ll n, m; cin >> n >> m;
    vector<ll> v(m);
    for(int i = 0; i < m; i++){
        cin >> v[i];
    }
    ll ans = 0;
    for(int i = 1; i < (1 << m); i++){
        vector<ll> nums;    ll maxin = 0;
        for(int j = 0; j < m; j++){
            if(i & (1 << j)){
                nums.push_back(v[j]);
                if(!maxin) maxin = v[j];
                else maxin = __gcd(maxin, v[j]);
            }
        }
        if(nums.size() == 1) ans += n / nums[0];
        else {
            ll mul = 1; bool can = 1;
            nums[0] /= maxin;
            for(auto &x : nums){
                if(overflow(mul, x, n)){
                    can = 0; break;
                }
                mul = mul * x;
            }
            if(can){
                if(nums.size() & 1){
                    ans += n / mul;
                }
                else ans -= n / mul;
            }
        }
    }
    cout << ans;
}