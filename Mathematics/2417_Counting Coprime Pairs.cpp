#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int mod = 1e9 + 7;
void init(vector<int> &mobius, int mx) {
    mobius.resize(mx + 1, 0);
    mobius[1] = 1;
    vector<int> wei(mx + 1);  // wei = 0 代表是質數，-1 代表可被平方數整除
    for (int i = 2; i <= mx; i++) {
        if (wei[i] == -1) {
            mobius[i] = 0;
            continue; // 包含平方
        }
        if (wei[i] == 0) {
            wei[i] = 1;
            for (int j = 2; i * j <= mx; j++) {
                if (j % i == 0) wei[i * j] = -1;
                else if (wei[i * j] != -1) wei[i * j]++;
            }
        }
        mobius[i] = wei[i] % 2 == 0 ? 1 : -1;
    }
}

void solve() {
    int n; cin >> n;
    vector<int> v(n), mobius;
    for (int i = 0; i < n; i++) {
        cin >> v[i];
    }
    int mx = *max_element(all(v));
    vector<int> p(mx + 1);
    init(mobius, mx);
    for (auto i : v) p[i]++;
    for (int i = 1; i <= mx; i++) {
        for (int j = 2; i * j <= mx; j++) {
            p[i] += p[i * j];
        }
    }
    for (auto &x : p) x = x * (x - 1) / 2;
    int ans = 0;
    for (int i = 1; i <= mx; i++) {
        ans += mobius[i] * p[i];
    }
    cout << ans << "\n";
}
 
signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}