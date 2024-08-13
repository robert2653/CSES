#include <bits/stdc++.h>
#pragma GCC optimize ("03")
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, x; cin >> n >> x;
    int sum = 0;
    unordered_map<int, int> mp;
    mp[0] = 1;
    int ans = 0;
    while(n--){
        int tmp; cin >> tmp;
        sum += tmp;
        ans += mp[sum - x];
        mp[sum]++;
    }
    cout << ans;
}