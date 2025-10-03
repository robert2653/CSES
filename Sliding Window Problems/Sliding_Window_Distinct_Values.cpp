#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, k;
    cin >> n >> k;
    map<int, int> mp;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int r = 0; r < n; r++) {
        mp[a[r]]++;
        if (mp[a[r]] == 1) {
            ans++;
        }
        if (r >= k) {
            mp[a[r - k]]--;
            if (mp[a[r - k]] == 0) {
                ans--;
            }
        }
        if (r >= k - 1) {
            cout << ans << " \n"[r == n - 1];
        }
    }
    return 0;
}