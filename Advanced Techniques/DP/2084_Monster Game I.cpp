#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Line {
    ll m, b;
    Line(ll m, ll b) : m(m), b(b) {}
};
bool intersectBefore(const Line& l1, const Line& l2, const Line& l3) {
    return (l3.b - l2.b) * (l1.m - l3.m) <= (l3.b - l1.b) * (l2.m - l3.m);
}
ll calcDP(ll m, ll x, ll b) {
    return m * x + b;
}
// dp[i] = min(fj * s[i] + dp[j])
// 維護上凸包
void solve() {
    int n; ll x;
    cin >> n >> x;
    vector<ll> s(n), f(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> f[i];

    deque<Line> hull;
    hull.emplace_back(x, 0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        while (hull.size() >= 2 && calcDP(hull[0].m, s[i], hull[0].b) >= calcDP(hull[1].m, s[i], hull[1].b)) {
            hull.pop_front(); // 查詢已經超過左線段了
        }
        ll dp = calcDP(hull[0].m, s[i], hull[0].b);
        if (i == n - 1) ans = dp;
        Line newLine(f[i], dp);
        while (hull.size() >= 2 && intersectBefore(hull[hull.size() - 2], hull.back(), newLine)) {
            hull.pop_back();
        }
        hull.push_back(newLine);
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