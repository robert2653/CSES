#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<vector<pair<int, int>>> qry(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        qry[l - 1].emplace_back(r - 1, i);
    }
    vector<int> ans(q);
    vector<int> stk;
    for (int l = n - 1; l >= 0; l--) {
        while (!stk.empty() && a[l] >= a[stk.back()]) {
            stk.pop_back();
        }
        stk.push_back(l);
        for (auto [r, id] : qry[l]) {
            int p = upper_bound(stk.rbegin(), stk.rend(), r) - stk.rbegin();
            ans[id] = p;
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}