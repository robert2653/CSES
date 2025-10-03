#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    map<int, int> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    int cnt = 0;
    for (int l = 0, r = 0; r < n; r++) {
        int x = a[r];
        mp[x]++;
        if (mp[x] == 1) {
            cnt++;
        }
        while (cnt != r - l + 1) {
            int y = a[l];
            mp[y]--;
            if (mp[y] == 0) {
                cnt--;
            }
            l++;
        }
        ans += r - l + 1;
    }
    cout << ans << "\n";
    return 0;
}