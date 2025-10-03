#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;
    deque<pair<int, int>> dq;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        while (!dq.empty() && dq.back().second > x) {
            dq.pop_back();
        }
        dq.emplace_back(i, x);
        while (dq.front().first <= i - k) {
            dq.pop_front();
        }
        if (i >= k - 1) {
            ans ^= dq.front().second;
        }
        x = (1LL * a * x + b) % c;
    }
    cout << ans << "\n";
    return 0;
}