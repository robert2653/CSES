#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()

using namespace std;
using ll = long long;

void solve() {
    struct E {
        int from, to, w, id;
        bool operator<(const E &rhs) {
            return to == rhs.to ? w > rhs.w : to < rhs.to;
    }};
    int n; cin >> n;
    vector<E> a(n + 1);
    for (int i = 1; i <= n; i++) {
        int u, v, w; cin >> u >> v >> w;
        a[i] = {u, v, w, i};
    }
    vector<array<ll, 2>> dp(n + 1); // w, time
    vector<array<int, 2>> rec(n + 1); // 有沒選，上個是誰
    sort(a.begin(), a.end());
    for (int i = 1; i <= n; i++) {
        auto it = --lower_bound(all(a), E({0, a[i].from}),
        [](E x, E y){ return x.to < y.to; });
        int id = it - a.begin(); dp[i] = dp[i - 1];
        ll nw = dp[id][0] + a[i].w;
        ll nt = dp[id][1] + a[i].to - a[i].from;
        if (dp[i][0] < nw || dp[i][0] == nw && dp[i][1] > nt) {
            dp[i] = {nw, nt}; rec[i] = {1, id};
        }
    }
    vector<int> ans;
    for (int i = n; i != 0;) {
        if (rec[i][0]) {
            ans.push_back(a[i].id);
            i = rec[i][1];
        } else i--;
    }
    cout << ans.size() << " " << dp[n][0] << " " << dp[n][1] << "\n";
    sort(all(ans)); for (auto x : ans) cout << x << " ";
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