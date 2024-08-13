#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
using namespace std;
using ll = long long;

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    set<int> leaf;
    map<int, int> mp;
    // 不在 a 裡的說明他是 leaf, 只要把最小的 leaf 取出來跟 a[i] 建邊就行, 然後如果 a[i] 沒有這個 node 了, 就加進 leaf 裡, 最後的最後, leaf 有兩個節點, 連邊

    for (int i = 1; i <= n; i++) {
        leaf.insert(i);
    }

    for (int i = 0; i < n - 2; i++) {
        cin >> a[i];
        mp[a[i]]++;
        leaf.erase(a[i]);
    }

    for (int i = 0; i < n - 2; i++) {
        int x = *leaf.begin();
        leaf.erase(x);
        cout << x << " " << a[i] << "\n";
        mp[a[i]]--;
        if (mp[a[i]] == 0) {
            mp.erase(a[i]);
            leaf.insert(a[i]);
        }
    }

    cout << *leaf.begin() << " " << *leaf.rbegin() << "\n";
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