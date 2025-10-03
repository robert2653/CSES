#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k, x, a, b, c;
    cin >> n >> k >> x >> a >> b >> c;
    vector<int> arr(n);
    arr[0] = x;
    for (int i = 1; i < n; i++) {
        arr[i] = (1LL * a * arr[i - 1] + b) % c;
    }
    // for (int i = 0; i < n; i++) {
    //     cerr << arr[i] << " \n"[i == n - 1];
    // }
    int blk = (n + k - 1) / k;
    vector<int> pref = arr, suff = arr;
    for (int i = 0; i < blk; i++) {
        int l = i * k + 1, r = min(n, (i + 1) * k);
        for (int j = l; j < r; j++) {
            pref[j] |= pref[j - 1];
        }
        for (int j = r - 2; j >= l - 1; j--) {
            suff[j] |= suff[j + 1];
        }
    }
    // for (int i = 0; i < n; i++) {
    //     cerr << pref[i] << " \n"[i == n - 1];
    // }
    // for (int i = 0; i < n; i++) {
    //     cerr << suff[i] << " \n"[i == n - 1];
    // }
    int ans = 0;
    for (int i = k - 1; i < n; i++) {
        ans ^= pref[i] | suff[i - k + 1];
        // cerr << (pref[i] | suff[i - k + 1]) << " \n"[i == n - 1];
    }
    cout << ans << "\n";

    return 0;
}