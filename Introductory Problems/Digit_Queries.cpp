#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll power(ll x, ll b) {
    ll res = 1;
    for (int i = 0; i < b; i++) {
        res *= x;
    }
    return res;
}

void solve() {
    vector<ll> a(19);
    a[0] = 1;
    for (int i = 1; i <= 18; i++) {
        a[i] = 9LL * power(10LL, i - 1);
    }
    int n; cin >> n;
    while (n--) {
        ll x; cin >> x;
        int i = 1;
        for (; i <= 18; i++) {
            if (x > a[i] * i) {
                x -= a[i] * i;
            } else {
                break;
            }
        }
        vector<int> ans(i); ans[i - 1] = 1;
        for (int j = i - 1; j >= 0; j--) {
            ll res = (x - 1) / (power(10, j) * i);
            ans[j] += res;
            x -= res * i * power(10, j);
        }
        cout << ans[i - x] << "\n";
    }
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