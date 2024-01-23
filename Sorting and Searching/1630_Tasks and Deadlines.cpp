#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n; cin >> n;
    vector<pair<int, int>> v(n);
    for(int i = 0; i < n; i++) cin >> v[i].first >> v[i].second;
    sort(v.begin(), v.end());
    int now = 0; int ans = 0;
    for(int i = 0; i < n; i++){
        now += v[i].first;
        ans += v[i].second - now;
    }
    cout << ans;
}