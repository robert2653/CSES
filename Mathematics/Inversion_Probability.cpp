#include <bits/stdc++.h>

using namespace std;
using ll = long long;
constexpr double eps = 1e-8;

void solve() {
    double ans = 0.0;
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ll x = 1;
            if (a[i] <= a[j]) {
                x = a[i] * (a[i] - 1) / 2;
            } else {
                x = (a[j] + 1) * a[j] / 2 + (a[i] - a[j] - 1) * a[j];
            }
            ans += (double)x / (double)a[i] / (double)a[j];
        }
    }
    ans = llround(ans * 1e6 + ((int)ans & 1 ? eps : -eps)) / 1e6;
    cout << fixed << setprecision(6) << ans << "\n";
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