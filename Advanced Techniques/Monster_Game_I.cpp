#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 應用: dp(x) = C(x) + min/max(A(i) * x + B(i)), for i < x
struct Line {
    ll m, b;
    Line(ll m = 0, ll b = 0) : m(m), b(b) {}
    ll eval(ll x) { return m * x + b; }
};
struct CHT { // 斜率單調
    int lptr = 0, rptr = 0;
    vector<Line> hull;
    CHT(Line init = Line()) { hull.push_back(init); }
    bool frontBad(Line &l1, Line &l2, ll x) {
        // 斜率遞減、查詢遞增，因此只要左直線的 Y >= 右直線的 Y
        // 代表查詢的當下，右線段的高度已經低於左線段了
        return l1.eval(x) >= l2.eval(x);
    }
    bool backBad(Line &l1, Line &l2, Line &l3) {
        // 斜率遞減、上凸包、取 min
        // 因此只要 l2 跟 l3 的 X 交點 <= l1 跟 l3 的 X 交點，l2 就用不到了
        return (l3.b - l2.b) * (l1.m - l3.m) <= (l3.b - l1.b) * (l2.m - l3.m);
    }
    void addLine(Line l) {
        while (rptr - lptr > 0 && backBad(hull[rptr - 1], hull[rptr], l))
            hull.pop_back(), rptr--;
        hull.push_back(l), rptr++;
    }
    ll query(ll x) {
        while (rptr - lptr > 0 && frontBad(hull[lptr], hull[lptr + 1], x))
            lptr++;
        return hull[lptr].eval(x);
    }
};
void solve() {
    // dp[i] = min(fj * s[i] + dp[j])
    // 維護上凸包
    int n; ll x;
    cin >> n >> x;
    vector<ll> s(n), f(n);
    for (int i = 0; i < n; i++) cin >> s[i];
    for (int i = 0; i < n; i++) cin >> f[i];

    CHT cht(Line(x, 0));
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        ll dp = cht.query(s[i]);
        if (i == n - 1) ans = dp;
        cht.addLine(Line(f[i], dp));
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