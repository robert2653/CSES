#include <bits/stdc++.h>
#pragma GCC target("popcnt")

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<bitset<3000>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll x = (a[i] & a[j]).count();
            ans += x * (x - 1) / 2;
        }
    }

    cout << ans << "\n";
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