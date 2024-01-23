#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int n; cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    ll ans = v[0], pref = v[0];
    for(int i = 1; i < n; i++){
        pref = max(v[i] + pref, v[i]);
        ans = max(ans, pref);
    }
    std::cout << ans;
}