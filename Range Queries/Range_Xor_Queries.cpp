#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        a[i] ^= a[i - 1];
    }
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << (a[r] ^ a[l - 1]) << "\n";
    }
    
    return 0;
}