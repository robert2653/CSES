#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct SuffixArray {
    int n; vector<int> sa, rk, lc;
    // n: 字串長度
    // sa: 後綴數組，sa[i] 表示第 i 小的後綴的起始位置
    // rk: 排名數組，rk[i] 表示從位置 i 開始的後綴的排名
    // lc: LCP 數組，lc[i] 表示 sa[i] 和 sa[i+1] 的最長公共前綴長度
    SuffixArray(const string &s) {
        n = s.length();
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
};

struct SAM { // 1 is initial state, 1-based
    static constexpr int ALPHABET_SIZE = 26;
    struct Node {
        int len;
        int link;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, next{} {}
    };
    vector<Node> t;
    SAM() {
        init();
    }
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};

void solve() {
    string s; cin >> s;
    int n = s.length();
    vector<int> last(n + 1); // s[i - 1] 的後綴終點位置
    last[0] = 1;
    SAM sam;
    for (int i = 0; i < n; i++) {
        last[i + 1] = sam.extend(last[i], s[i] - 'a');
    }
    int sz = sam.t.size();
    vector<int> cnt(sz);
    for (int i = 1; i <= n; i++) cnt[last[i]]++;
    vector<vector<int>> order(sz);
    for (int i = 1; i < sz; i++) {
        order[sam.t[i].len].push_back(i);
    }
    for (int i = sz - 1; i > 0; i--) {
        for (int u : order[i]) {
            if (sam.t[u].link != -1) {
                cnt[sam.t[u].link] += cnt[u];
            }
        }
    }

    int q; cin >> q;
    while (q--) {
        string sub; cin >> sub;
        int p = 1;
        for (int i = 0; i < sub.size(); i++) {
            p = sam.t[p].next[sub[i] - 'a'];
            if (p == 0) break;
        }
        cout << cnt[p] << "\n";
    }


    // string s;
    // cin >> s;
    // int n = s.size();

    // SuffixArray SA(s);

    // int q;
    // cin >> q;

    // for (int i = 0; i < q; i++) {
    //     string t; cin >> t;
    //     int m = t.length();
    //     // sa[i] 表示第 i 小的后缀的起始位置，所以可以二分搜找到跟 t 長度一樣且跟 t 長的一模一樣的 sa 位置
        
    //     int low = lower_bound(SA.sa.begin(), SA.sa.end(), t, [&](int i, const string& t) {
    //         return s.compare(i, m, t) < 0;
    //     }) - SA.sa.begin();
        
    //     int high = upper_bound(SA.sa.begin(), SA.sa.end(), t, [&](const string& t, int i) {
    //         return s.compare(i, m, t) > 0;
    //     }) - SA.sa.begin();
        
    //     cout << high - low << "\n";
    // }
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