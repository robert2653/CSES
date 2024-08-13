#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define int long long
using namespace std;
const int mod = 1e9 + 7;

void solve(){
    int n; cin >> n;
    vector<pair<int, int>> stk;
    stk.push_back({0, 0});
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        while (stk.back().first >= x) stk.pop_back();
        cout << stk.back().second << " ";
        stk.push_back({x, i + 1});
    }
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}