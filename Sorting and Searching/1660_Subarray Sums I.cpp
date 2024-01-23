#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, x; cin >> n >> x;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    int l = 0, r = -1, now = 0;
    int ans = 0;
    while(r < n){
        if(now >= x){
            now -= v[l];
            l++;
        }
        else if(r < n){
            now += v[r + 1];
            r++;
        }
        if(now == x) ans++;
    }
    cout << ans;
}