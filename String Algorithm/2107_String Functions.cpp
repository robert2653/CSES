#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// z[i] 表示 s 和 s[i, n - 1] (以 s[i] 開頭的後綴)
// 的最長公共前綴 (LCP) 的長度
vector<int> Z(string s) {
    int n = s.size();
    vector<int> z(n);
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
    return z; // 最後一格不算
}

struct KMP {
    string sub;
    vector<int> failure;
    KMP(string sub_) {
        sub = sub_;
        failure.resize(sub.size(), -1);
        buildFailFunction();
    }
    void buildFailFunction() {
        for (int i = 1; i < (int)sub.size(); i++) {
            int now = failure[i - 1];
            while (now != -1 && sub[now + 1] != sub[i]) now = failure[now];
            if (sub[now + 1] == sub[i]) failure[i] = now + 1;
        }
    }
    vector<int> match(string &s) {
        vector<int> match;
        for (int i = 0, now = -1; i < (int)s.size(); i++) {
            // now is the compare sucessed length -1
            while (s[i] != sub[now + 1] && now != -1) now = failure[now];
            // failure stores if comparison fail, move to where
            if (s[i] == sub[now + 1]) now++;
            if (now + 1 == (int)sub.size()) {
                match.push_back(i - now);
                now = failure[now];
            }
        }
        return match;
    }
};

void solve() {
    string s; cin >> s;
    int n = s.size();
    KMP kmp(s);
    vector<int> z = Z(s);
    z.front() = 0;
    for (auto i : z) {
        cout << i << " ";
    }
    cout << "\n";
    for (auto i : kmp.failure) {
        cout << i + 1 << " ";
    }
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