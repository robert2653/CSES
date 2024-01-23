#include <bits/stdc++.h>
#pragma GCC optimize ("03")
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    int sum = 0;
    vector<int> v(n, 0);
    v[0] = 1;
    int ans = 0;
    for(int i = 0; i < n; i++){
        int tmp; cin >> tmp;
        sum += tmp;
        ans += v[(sum % n + n) % n];
        v[(sum % n + n) % n]++;
    }
    cout << ans;
}