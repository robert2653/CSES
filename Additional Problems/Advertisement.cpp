#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> stk; // 紀錄所有籬笆比自己高的左界，以 (L, H) 紀錄，並且 L 是遞增的
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int l = i;
        while (!stk.empty() && stk.back().second >= a[i]) {
            auto [L, H] = stk.back();
            // stk.back 的狀態無法延續到 i，因為 a[i] 比 H 更低，所以考慮以 H 更新答案
            ans = max(ans, 1LL * (i - L) * H);
            l = L;
            stk.pop_back();
        }
        stk.emplace_back(l, a[i]);
    }
    while (!stk.empty()) {
        auto [L, H] = stk.back();
        ans = max(ans, 1LL * (n - L) * H); // 到 a[n - 1] 狀態都成立，所以用 n 去減
        stk.pop_back();
    }

    cout << ans << "\n";
    return 0;
}