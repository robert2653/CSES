#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int mex = 1;
    int n; cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for (auto x : a) {
        if (x == mex) mex++;
    }
    cout << mex << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}