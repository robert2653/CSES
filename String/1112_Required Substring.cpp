#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int mxN = 1001;
const int mxM = 101;
const int mxK = 26;
const int Mod = 1e9 + 7;

ll dp[mxN][mxM];

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

ll power(ll a, ll b) {
    ll res = 1;
    for (; b; b /= 2, (a *= a) %= Mod) {
        if (b % 2) {
            (res *= a) %= Mod;
        }
    }
    return res;
}

void solve() {
    int n; cin >> n;
    string s; cin >> s;
    int m = s.size();

    KMP kmp(s);
    
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (char c = 'A'; c <= 'Z'; c++) {
                int k = j - 1;
                while (k != -1 && c != s[k + 1])
                    k = kmp.failure[k];
                if (c == s[k + 1])
                    k++;
                dp[i + 1][k + 1] = (dp[i + 1][k + 1] + dp[i][j]) % Mod;
            }
        }
    }

    ll ans = 0;
    for (int j = 0; j < m; j++) {
        ans = (ans + dp[n][j]) % Mod;
    }
    
    cout << ((power(26, n) - ans) + Mod) % Mod << "\n";
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