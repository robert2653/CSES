#include <bits/stdc++.h>

using namespace std;
using ll = long long;
using ld = long double;

// uniform random variable
// E[X] = (L + 1) / 2;
void solve() {
    ld a, k;
    ld mean = (k + 1) / 2;
    ld var = (k * k - 1) / 12;
    cin >> a >> k;
    ld ans = 0;
    cout << fixed << setprecision(6) << a * (k + 1) / 2 << "\n";
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