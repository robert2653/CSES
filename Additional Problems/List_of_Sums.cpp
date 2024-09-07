#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// a0 = x, a1 = b0 - x, a2 = b1 - x;
// a1 + a2 = b2..., bn
// b0 + b1 - 2x = b2..., bn
// get a0 = x
// 知道 a0, a1, a2 後，每次挑最小的 b 跟 a0 配，加在 a 陣列的最後，找不到代表 a0 是錯的

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    int m = n * (n - 1) / 2;
    vector<int> b(m);
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    sort(b.begin(), b.end());

    for (int i = 2; i < m; i++) {
        int x = b[0] + b[1] - b[i];
        if (x <= 0 || x % 2 != 0) continue;
        x /= 2;
        vector<int> a {x};
        multiset<int> st(b.begin(), b.end());
        bool ok = true;
        for (int j = 1; j < n && ok; j++) {
            a.push_back(*st.begin() - a[0]);
            for (int k = 0; k < j; k++) {
                int y = a[k] + a[j];
                if (st.find(y) == st.end()) {
                    ok = false;
                    break;
                } else {
                    st.erase(st.find(y));
                }
            }
        }
        if (ok) {
            for (auto x : a) {
                cout << x << " ";
            }
            return 0;
        }
    }

    return 0;
}