#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll n; cin >> n;
    for (ll i = 1; i <= n; i++) {
        ll x = i * i;;
        ll ans = x * (x - 1) / 2;
        if (i >= 3) {
            ans -= 4 * (i - 1) * (i - 2);
        }
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}