#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

// 樹套樹，寫兩層 zkw

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<int>> g(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        for (int j = 0; j < n; j++) {
            g[i][j] = s[j] == '*';
        }
    }

    vector<vector<int>> a(n * 2, vector<int>(n * 2));
    auto add = [&](vector<int> &a, int x, int i) -> void {
        a[x += n] += i;
        for (x /= 2; x; x /= 2) a[x] = a[2 * x] + a[2 * x + 1];
    };
    auto add2 = [&](int y, int x, int i) -> void {
        for (y += n; y; y /= 2) add(a[y], x, i);
    };
    auto query = [&](vector<int> &a, int l, int r) -> int {
        int x = 0, y = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = x + a[l++];
            if (r & 1) y = a[--r] + y;
        }
        return x + y;
    };
    auto query2 = [&](int l, int r, int l2, int r2) -> int {
        int x = 0, y = 0;
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = x + query(a[l++], l2, r2);
            if (r & 1) y = query(a[--r], l2, r2) + y;
        }
        return x + y;
    };

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (g[i][j]) add2(i, j, 1);
        }
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int y, x;
            cin >> y >> x;
            y--;
            x--;
            add2(y, x, (g[y][x] ^= 1) ? 1 : -1);
        } else {
            int y1, x1, y2, x2;
            cin >> y1 >> x1 >> y2 >> x2;
            cout << query2(y1 - 1, y2, x1 - 1, x2) << "\n";
        }
    }
    
    return 0;
}