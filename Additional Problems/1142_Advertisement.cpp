#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<pair<ll, ll>> stk; // increasing, l side, h
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll h; cin >> h;
        ll l = i;
        while (!stk.empty() && stk.back().second >= h) {
            ans = max((i - stk.back().first) * stk.back().second, ans);
            l = stk.back().first;
            stk.pop_back();
        }
        stk.emplace_back(l, h);
        if (i == n - 1) {
            while (!stk.empty()) {
                ans = max(ans, (n - stk.back().first) * stk.back().second);
                stk.pop_back();
            }
        }
    }
    cout << ans << "\n";
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