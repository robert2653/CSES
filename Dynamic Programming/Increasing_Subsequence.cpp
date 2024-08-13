#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) cin >> v[i];
    int dp[n]; vector<int> stk;
    stk.push_back(v[0]);
    dp[0] = 1;  int L = 1;
    for (int i = 1; i < n; i++) {
        if (v[i] > stk.back()) {
            stk.push_back(v[i]);
            dp[i] = ++L;
        } else {
            auto it = lower_bound(stk.begin(), stk.end(), v[i]);
            *it = v[i]; dp[i] = it - stk.begin() + 1;
        }
    }
    vector<int> ans; cout << L << "\n";
    // for (int i = n - 1; i >= 0; i--) {
    //     if (dp[i] == L) {
    //         ans.push_back(v[i]), L--;
    //     }
    // }
    // reverse(ans.begin(), ans.end());
    // for (auto i : ans) cout << i << " ";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}