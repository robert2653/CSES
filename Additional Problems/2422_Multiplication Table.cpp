#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    ll n; cin >> n;
    ll tar = n * n / 2 + 1;
    // 1 2 3 4 5
    // 2 4 6 8 10
    // 3 6 9 12 15
    // 4 8 12 16 20
    // 5 10 15 20 25
    ll l = 0, r = 1e12;
    auto f = [&](ll m) -> bool {
        ll sum = 0;
        for (ll i = 1; i <= n; i++) {
            sum += min(n, m / i);
            if (sum >= tar) return true;
        }
        return false;
    };
    while (l <= r) {
        ll m = (l + r) / 2;
        if (f(m)) {
            r = m - 1;
        } else {
            l = m + 1;
        }
    }
    cout << l << "\n";
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