#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll ans = 0;
    int n, k;
    cin >> n >> k;
    int x, a, b, c;
    cin >> x >> a >> b >> c;
    int now = x, pre = 0;
    ll sum = 0;
    for (int r = 0; r < n; r++) {
        sum += now;
        if (r >= k) {
            sum -= pre;
        }
        if (r >= k - 1) {
            ans ^= sum;
        }
        pre = (1LL * a * pre + b) % c;
        now = (1LL * a * now + b) % c;
        if (r == k - 1) {
            pre = x;
        }
    }
    cout << ans << "\n";
    return 0;
}