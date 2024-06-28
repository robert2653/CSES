#include <bits/stdc++.h>
using namespace std;

using ll = long long;

void solve() {
    int n, q; cin >> n >> q;
    vector<int> pos(n);
    vector<int> a(n), b(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[a[i] - 1] = i;
        pos[i] = a[i] - 1;
    }

    int ans = 1;
    for (int i = 1; i < n; i++) {
        if (b[i - 1] > b[i]) {
            ans++;
        }
    }

    for (int i = 0; i < q; i++) {
        int x, y; cin >> x >> y;
        x--; y--;
        int pos_x = pos[x], pos_y = pos[y];
        if (pos_x > pos_y) {
            swap(pos_x, pos_y);
            swap(x, y);
        }

        auto f = [&](int p, int new_val, int q) -> int {
            int ans = 0;
            if (p >= 1 && p - 1 != q) {
                if (b[p - 1] > b[p] && b[p - 1] < new_val) ans--;
                if (b[p - 1] < b[p] && b[p - 1] > new_val) ans++;
            }
            if (p + 1 < n && p + 1 != q) {
                if (b[p] > b[p + 1] && new_val < b[p + 1]) ans--;
                if (b[p] < b[p + 1] && new_val > b[p + 1]) ans++;
            }
            return ans;
        };

        ans += f(pos_x, y, pos_y) + f(pos_y, x, pos_x);
        if (pos_y - pos_x == 1) {
            if (x > y) ans--;
            else ans++;
        }
        // cerr << pos_x << " " << pos_y << "\n";

        swap(b[pos_x], b[pos_y]);
        swap(pos[x], pos[y]);
        // for (auto i : pos) cout << i << " "; cout << "\n";
        // for (auto i : b) cout << i << " "; cout << "\n";

        cout << ans << "\n";
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