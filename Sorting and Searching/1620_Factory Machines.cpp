// 二分搜
#include <bits/stdc++.h>
using namespace std;
#define int long long
bool check(vector<int> &machine_time, int x, int t){
    int ans = 0;
    for(auto &i : machine_time) {
        ans += x / i;
        if(ans >= t) return true;
    }
    return false;
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int n, t; cin >> n >> t;
    vector<int> machine_time(n);
    for(int i = 0; i < n; i++){
        cin >> machine_time[i];
    }
    int l = 0, r = 2e18;
    while(l <= r){
        int mid = (l + r) / 2;
        if(check(machine_time, mid, t)) r = mid - 1;
        else l = mid + 1;
    }
    cout << l << "\n";
}