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
    vector<int> basis;
    auto add = [&](vector<int> &basis, int x) {
        for (auto i : basis) {
            x = min(x, x ^ i);
        }
        if (x) basis.push_back(x);
    };
    for (auto i : a) {
        add(basis, i);
    }
    sort(basis.rbegin(), basis.rend());
    int ans = 0;
    for (auto i : basis) {
        ans = max(ans, ans ^ i);
    }
    cout << ans << "\n";
    return 0;
}