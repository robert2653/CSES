#include <bits/stdc++.h>
#pragma GCC target("popcnt")

using namespace std;
using ll = long long;

void solve() {
    int n, len;
    cin >> n >> len;
    vector<bitset<30>> v(n);
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        v[i] = bitset<30>(s);
    }

    int ans = 31;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            ans = min<int>((v[i] ^ v[j]).count(), ans);
        }
    }

    cout << ans << "\n";
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