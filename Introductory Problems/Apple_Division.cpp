#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr ll inf = 4E18;

void solve() {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll s = accumulate(a.begin(), a.end(), 0LL);
    ll ans = inf;
    for (int i = 0; i < (1 << n); i++) {
        ll sum = 0;
        for (int j = 0; j < n; j++) {
            if (i >> j & 1) {
                sum += a[j];
            }
        }
        // cerr << sum << "\n";
        ans = min(ans, llabs(s - sum - sum));
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
    return 0;
}