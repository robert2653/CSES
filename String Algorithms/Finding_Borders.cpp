#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
using namespace std;
const int mod = 1e9 + 7;

// z[i] 表示 s 和 s[i, n - 1] (以 s[i] 開頭的後綴)
// 的最長公共前綴 (LCP) 的長度
vector<int> Z(const string &s) {
    int n = s.size();
    vector<int> z(n);
    z[0] = n; // lcp(s, s), -1 or n
    for (int i = 1, j = 1; i < n; i++) {
        z[i] = max(0, min(j + z[j] - i, z[i - j]));
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            z[i]++;
        }
        if (i + z[i] > j + z[j]) j = i;
    }
    return z;
}

void solve() {
    string s; 
    cin >> s;
    int n = s.length();
    vector<int> res = Z(s);

    vector<int> ans;
    for (int i = 1; i < s.size(); i++) {
        if (res[i] == n - i) {
            ans.push_back(res[i]);
        }
    }

    sort(ans.begin(), ans.end());
    ans.reserve(unique(ans.begin(), ans.end()) - ans.begin());

    for (auto x : ans) {
        cout << x << " \n"[x == ans.back()];
    }
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