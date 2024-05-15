#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int n; cin >> n;
    vector<ll> v(n);
    for(int i = 0; i < n; i++){
        ll tmp; cin >> tmp;
        v[i] = tmp;
    }
    sort(v.begin(), v.end());
    ll mid = v[n / 2];
    ll ans = 0;
    for(auto &i : v){
        ans += abs(i - mid);
    }
    cout << ans;
}