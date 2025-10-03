#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, a, b;
    cin >> n >> a >> b;
    if (a + b > n) {
        cout << "NO\n";
        return;
    }
    int fair = n - a - b;
    if ((a == 0) ^ (b == 0)) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    // 1 2 3 4
    // 1 2 3 4
    vector<int> ans(fair);
    iota(ans.begin(), ans.end(), 1);
    for (int i = a; i >= 1; i--) {
        ans.push_back(n - i + 1);
    }
    for (int i = fair + 1; ans.size() < n; i++) {
        ans.push_back(i);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " \n"[i == n - 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}