#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    ll x; cin >> x;

    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    vector<int> a1, a2;
    int middle = n / 2 - 1; // pos
    a1.reserve(1 << (middle + 1));
    a2.reserve(1 << (n - middle));

    auto dfs = [&](auto &&self, int i, int end, ll now, vector<int> &v) -> void {
        if (now > x) return;
        if (i > end) {
            v.push_back(now);
            return;
        }
        self(self, i + 1, end, now, v);
        self(self, i + 1, end, now + a[i], v);
    };
    dfs(dfs, 0, middle, 0LL, a1);
    dfs(dfs, middle + 1, n - 1, 0LL, a2);

    sort(a2.begin(), a2.end());
    ll ans = 0;
    for (auto i : a1) {
        auto l = lower_bound(a2.begin(), a2.end(), x - i);
        if (l != a2.end() && *l != x - i) continue;
        auto r = --upper_bound(a2.begin(), a2.end(), x - i);
        ans += r - l + 1;
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