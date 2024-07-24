#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SuffixArray {
    int n; string s;
    vector<int> sa, rk, lc;
    // n: 字串長度
    // sa: 後綴數組，sa[i] 表示第 i 小的後綴的起始位置
    // rk: 排名數組，rk[i] 表示從位置 i 開始的後綴的排名
    // lc: LCP 數組，lc[i] 表示 sa[i] 和 sa[i + 1] 的最長公共前綴長度
    SuffixArray(const string &s_) {
        s = s_; n = s.length();
        sa.resize(n);
        lc.resize(n - 1);
        rk.resize(n);
        iota(sa.begin(), sa.end(), 0);
        sort(sa.begin(), sa.end(), [&](int a, int b) { return s[a] < s[b]; });
        rk[sa[0]] = 0;
        for (int i = 1; i < n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; ++i)
                tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; ++i)
                ++cnt[rk[i]];
            for (int i = 1; i < n; ++i)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; --i)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; ++i)
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; ++i) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; )
                    ++j;
                lc[rk[i] - 1] = j;
            }
        }
    }
    string getLCP() {
        int cp = 0, k, lcp = 0, p;
        for (int i = 0; i < n; i++) {
            if (!rk[i]) continue;
            k = sa[rk[i] - 1];
            if (cp) cp--;
            while (s[i + cp] == s[k + cp]) cp++;
            if (cp > lcp){
                lcp = cp;
                p = i;
            }
        }
        if (lcp) {
            return s.substr(p, lcp);
        } else {
            return "-1";
        }
    }
};

void solve() {
    string s;
    cin >> s;
    int n = s.length();
    SuffixArray SA(s);

    ll k;
    cin >> k;

    for (int i = 0; i < n; i++) {
        int p = SA.sa[i];
        int m = n - p;
        // int lc = i > 0 ? SA.lc[i - 1] : 0;
        int lc = 0;
        m -= lc;
        if (k > m) {
            k -= m;
        } else {
            // 找第 m 大的
            cout << s.substr(p, k + lc) << "\n";
            return;
        }
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