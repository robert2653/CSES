#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int x;
    cin >> x;

    int ans = 0;
    while (x) {
        string s = to_string(x);
        int mx = *max_element(s.begin(), s.end()) - '0';
        x -= mx;
        ans++;
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}