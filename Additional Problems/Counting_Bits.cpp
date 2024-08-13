#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
using namespace std;
using ll = long long;

void solve() {
    ll x; cin >> x;
    int cnt = 0;
    ll ans = 0;

    int l = __lg(x);
    for (int i = l; i >= 0; i--) {
        if (x >> i & 1) {
            ans += (1LL << i) * cnt + 1LL * i * (1LL << (i - 1));
            cnt += 1;
        }
        // cerr << ans << "\n";
    }
    // 001
    // 010
    // 011
    // 100
    // 101
    // 110
    // 111
    cout << ans + cnt << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}