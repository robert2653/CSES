#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 編號小的指到邊號大的就一定無環
void solve() {
    int n; cin >> n;
    // vector g(n, vector<int>());
    int m; cin >> m;
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        cout << min(u, v) << " " << max(u, v) << "\n";
    }
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