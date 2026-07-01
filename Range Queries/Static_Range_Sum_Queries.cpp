#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<ll> a(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i + 1];
        a[i + 1] += a[i];
    }

    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << a[r] - a[l - 1] << "\n";
    }

    return 0;
}