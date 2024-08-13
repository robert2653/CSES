#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
using namespace std;
using ll = long long;

void solve() {
    string s;
    cin >> s;
    string t = "ATCG";
    map<char, int> mp;
    
    string ans;
    for (auto c : s) {
        mp[c]++;
        if (mp.size() == 4) {
            ans.push_back(c);
            mp.clear();
        }
    }

    for (auto c : t) {
        if (mp.count(c) == 0) {
            ans.push_back(c);
            break;
        }
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
    return 0;
}