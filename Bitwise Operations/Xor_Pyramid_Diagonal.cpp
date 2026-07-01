#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m = __lg(n) + 1;
    a.resize(1 << m);
    vector<int> dp = a;

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < 1 << m; j++) {
            if (j >> i & 1) {
                int p = j ^ (1 << i);
                dp[j] ^= dp[p];
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " \n"[i == n - 1];
    }
    return 0;
}