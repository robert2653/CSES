#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
using namespace std;
const int mod = 1e9 + 7;

// z[i] 表示 s 和 s[i, n - 1] (以 s[i] 開頭的後綴)
// 的最長公共前綴 (LCP) 的長度
vector<int> Z(string s) {
    int n = s.size();
    vector<int> z(n + 1);
    z[0] = n;
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = max(0, min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) {
            j = i;
        }
    }
    return z;
}

void solve() {
    string s; cin >> s;
    vector<int> res = Z(s);
    res.pop_back();

    vector<int> ans;
    for (int i = 1, n = s.size(); i < n; i++) {
        // cerr << i << " " << res[i] << "\n";
        if (res[i] + i == n) {
            ans.push_back(i);
        }
    }

    sort(ans.begin(), ans.end());
    int n = unique(ans.begin(), ans.end()) - ans.begin();

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
    }
    cout << s.size();
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}