#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    int mx; cin >> mx;
    long long ans = 0;
    while(--n){
        int now; cin >> now;
        if(now < mx)    ans += abs(now - mx);
        else mx = now;
    }
    cout << ans;
}