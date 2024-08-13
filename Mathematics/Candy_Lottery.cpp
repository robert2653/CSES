#include <bits/stdc++.h>

using namespace std;
using i64 = long long;
using ll = long long;

template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

// 最大是 i 的機率是 (i / k) ^ n - ((i - 1) / k) ^ n
void solve() {
    double n, k;
    cin >> n >> k;
    double ans = 0.0;
    for (int i = 1; i <= k; i++) {
        ans += i * (power(double(i) / k, n) - power((double(i - 1)) / k, n));
    }
    ans *= 1e6;
    ans = llround(ans);
    ans /= 1e6;
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