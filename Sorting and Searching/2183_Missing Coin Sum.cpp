#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int main(){
    int n; cin >> n;
    ll pref = 1;
    // if pref, x, I can genetate 1 to pref - 1
    // and generate pref to pref + x - 1 by 1 to pref - 1 and x;
    vector<ll> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    sort(v.begin(), v.end());
    for(auto &i : v){
        if(pref < i){
            cout << pref;
            return 0;
        }
        pref += i;
    }
    cout << pref;
}