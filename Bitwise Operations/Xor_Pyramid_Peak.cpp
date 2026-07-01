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
    // 1
    // 1 1
    // 1 2 1
    // 1 3 3 1
    // 1 4 6 4 1
    // 1 5 10 10 5 1
    // 1 6 15 20 15 6 1
    // 1 7 21 35 35 21 7 1
    // vector<int> fac_cnt_2(n);
    // for (int i = 2; i < n; i *= 2) {
    //     for (int j = i; j < n; j += i) {
    //         fac_cnt_2[j]++;
    //     }
    // }
    // for (int i = 1; i < n; i++) {
    //     fac_cnt_2[i] += fac_cnt_2[i - 1];
    // }
    // int ans = 0;
    // for (int i = 0; i < n; i++) {
    //     int u = fac_cnt_2[n - 1];
    //     int v = fac_cnt_2[i] + fac_cnt_2[n - 1 - i];
    //     // cerr << i << " " << u << " " << v << "\n";
    //     if (u == v) {
    //         ans ^= a[i];
    //     }
    // }
    // cout << ans << "\n";

    int ans = 0;
    n--;
    for (int i = 0; i <= n; i++) {
        if ((n & i) == i) {
            ans ^= a[i];
        }
    }
    cout << ans << "\n";
    return 0;
}