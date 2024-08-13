#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define int long long
using namespace std;
const int mod = 1e9 + 7;

void solve() {
    int n; cin >> n;
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x; cin >> x;
        ans ^= x;
    }
    if (ans == 0) cout << "second\n";
    else cout << "first\n";
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
}