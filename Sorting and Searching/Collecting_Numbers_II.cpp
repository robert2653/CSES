#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n), pos(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
        pos[a[i]] = i;
    }
    int ans = 1;
    for (int i = 0; i + 1 < n; i++) {
        if (pos[i] > pos[i + 1]) {
            ans++;
        }
    }
    auto f = [&](int x, int c) {
        if (x >= 0 && x < n - 1 && pos[x] > pos[x + 1]) {
            ans += c;
        }
    };
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        f(a[x] - 1, -1);
        if (a[x] + 1 != a[y]) f(a[x], -1);
        f(a[y] - 1, -1);
        if (a[y] + 1 != a[x]) f(a[y], -1);

        swap(a[x], a[y]);
        pos[a[x]] = x;
        pos[a[y]] = y;

        f(a[x] - 1, 1);
        if (a[x] + 1 != a[y]) f(a[x], 1);
        f(a[y] - 1, 1);
        if (a[y] + 1 != a[x]) f(a[y], 1);

        cout << ans << "\n";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve();

    return 0;
}