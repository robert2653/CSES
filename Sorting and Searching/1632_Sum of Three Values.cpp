#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
signed main(){
    #ifdef LOCAL
    freopen("1.in", "r", stdin);
    freopen("1.ans", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    sort(a.begin(), a.end());
    int ll = 0, rr = n - 1;
    while(ll <= rr){
        int mm = (ll + rr) / 2;
        if(a[mm].first >= k){
            rr = mm - 1;
        }
        else ll = mm + 1;
    }
    int side = rr;
    for(int i = 0; i <= side; i++){
        int x = k - a[i].first;
        int l = 0, r = n - 1;
        while(l < r){
            if(l == i){ l++; continue; }
            if(r == i){ r--; continue; }
            int sum = a[l].first + a[r].first;
            if(sum == x){
                cout << a[l].second + 1 << " " << a[r].second + 1 << " " << a[i].second + 1 << "\n";
                return 0;
            }
            else if(sum < x) l++;
            else r--;
        }
    }
    cout << "IMPOSSIBLE";
}