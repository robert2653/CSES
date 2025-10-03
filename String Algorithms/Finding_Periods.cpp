#include <bits/stdc++.h>
using namespace std;

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

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();
    vector<int> res = Z(s);

    vector<int> ans;
    for (int i = 1; i < s.size(); i++) {
        if (res[i] + i == n) {
            ans.push_back(i);
        }
    }
    ans.push_back(s.length());
    for (auto x : ans) {
        cout << x << " \n"[x == ans.back()];
    }

    return 0;
}