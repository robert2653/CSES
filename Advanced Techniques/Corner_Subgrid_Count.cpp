#include <bits/stdc++.h>
#pragma GCC target("popcnt")
 
using namespace std;
using ll = long long;
 
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<bitset<3000>> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int x = (a[i] & a[j]).count();
            ans += 1LL * x * (x - 1) / 2;
        }
    }
 
    cout << ans << "\n";
    return 0;
}