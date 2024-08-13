#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    int k; cin >> k;
    ll ans = 0;
    map<int, int> mp;
    int l = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = x;
        mp[x]++;
        while (mp.size() > k) {
            mp[a[l]]--;
            if (!mp[a[l]]) {
                mp.erase(a[l]);
            }
            l++;
        }
        ans += i - l + 1;
    }
    cout << ans << "\n";
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