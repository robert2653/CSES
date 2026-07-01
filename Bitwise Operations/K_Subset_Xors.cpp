#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
 
    int n, k;
    cin >> n >> k;
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
    for (int i = 0; i < n; i++) {
        add(basis, a[i]);
    }
    sort(basis.begin(), basis.end()); // 最簡化列梯
    for (auto i = basis.begin(); i != basis.end(); i++) {
        for (auto j = next(i); j != basis.end(); j++) {
            *j = min(*j, *j ^ *i);
        }
    }
 
    int lg = __lg(k);
    int rep = min(k, 1 << min(lg + 1, n - int(basis.size())));

    vector<int> v;
    for (int i = 0; k; i++) {
        int x = 0;
        for (int j = 0; j <= lg; j++) {
            if (i >> j & 1) {
                x ^= basis[j];
            }
        }
        for (int j = 0; j < rep && k; j++, k--) {
            cout << x << " ";
        }
    }
    return 0;
}