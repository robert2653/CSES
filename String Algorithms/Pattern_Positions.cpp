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
        for (int i = 1; i < n; i++)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
        int k = 1;
        vector<int> tmp, cnt(n);
        tmp.reserve(n);
        while (rk[sa[n - 1]] < n - 1) {
            tmp.clear();
            for (int i = 0; i < k; i++)
                tmp.push_back(n - k + i);
            for (auto i : sa)
                if (i >= k)
                    tmp.push_back(i - k);
            fill(cnt.begin(), cnt.end(), 0);
            for (int i = 0; i < n; i++)
                ++cnt[rk[i]];
            for (int i = 1; i < n; i++)
                cnt[i] += cnt[i - 1];
            for (int i = n - 1; i >= 0; i--)
                sa[--cnt[rk[tmp[i]]]] = tmp[i];
            swap(rk, tmp);
            rk[sa[0]] = 0;
            for (int i = 1; i < n; i++)
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] || sa[i - 1] + k == n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);
            k *= 2;
        }
        for (int i = 0, j = 0; i < n; i++) {
            if (rk[i] == 0) {
                j = 0;
            } else {
                for (j -= j > 0; i + j < n && sa[rk[i] - 1] + j < n && s[i + j] == s[sa[rk[i] - 1] + j]; j++);
                lc[rk[i] - 1] = j;
            }
        }
    }
};
 
template<class T, class F = less<T>>
struct RMQ { // [l, r)
    int n;
    F cmp = F();
    vector<vector<T>> g;
    RMQ() {}
    RMQ(const vector<T> &a, F cmp = F()) : cmp(cmp) {
        init(a);
    }
    void init(const vector<T> &a) {
        n = a.size();
        int lg = __lg(n);
        g.resize(lg + 1);
        g[0] = a;
        for (int j = 1; j <= lg; j++) {
            g[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++)
                g[j][i] = min(g[j - 1][i], g[j - 1][i + (1 << (j - 1))], cmp);
        }
    }
    T operator()(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int lg = __lg(r - l);
        return min(g[lg][l], g[lg][r - (1 << lg)], cmp);
    }
};

void solve_SA() {
    string s;
    cin >> s;
    int n = s.length();
 
    SuffixArray sa(s);
    RMQ<int> rmq(sa.sa);
 
    int q; cin >> q;
 
    for (int i = 0; i < q; i++) {
        string sub;
        cin >> sub;
        int lo = 0, hi = n;
        while (lo < hi) {
            int x = (lo + hi) / 2;
            if (s.compare(sa.sa[x], sub.length(), sub) >= 0) {
                hi = x;
            } else {
                lo = x + 1;
            }
        }
        int res = lo;
        lo = -1, hi = n - 1;
        while (lo < hi) {
            int x = (lo + hi + 1) / 2;
            if (s.compare(sa.sa[x], sub.length(), sub) <= 0) {
                lo = x;
            } else {
                hi = x - 1;
            }
        }
        cout << (lo - res + 1 == 0 ? -1 : rmq(res, lo + 1) + 1) << "\n";
    }
}

struct SAM {
    // 1 -> initial state
    static constexpr int ALPHABET_SIZE = 26;
    // node -> strings with the same endpos set
    // link -> longest suffix with different endpos set
    // len -> state's longest suffix
    // fpos -> first endpos
    // strlen range -> [len(link) + 1, len]
    struct Node {
        int len, link = -1, fpos;
        array<int, ALPHABET_SIZE> next;
    };
    vector<Node> t;
    SAM() : t(1) {}
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        t[cur].fpos = t[cur].len - 1;
        while (p != -1 && !t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        if (p == -1) {
            t[cur].link = 0;
        } else {
            int q = t[p].next[c];
            if (t[p].len + 1 == t[q].len) {
                t[cur].link = q;
            } else {
                int r = newNode();
                t[r] = t[q];
                t[r].len = t[p].len + 1;
                while (p != -1 && t[p].next[c] == q) {
                    t[p].next[c] = r;
                    p = t[p].link;
                }
                t[q].link = t[cur].link = r;
            }
        }
        return cur;
    }
};

void solve_SAM() {
    string s;
    cin >> s;
    SAM sam;
    int n = s.length();
    vector<int> last(n + 1);
    for (int i = 0; i < n; i++) {
        last[i + 1] = sam.extend(last[i], s[i] - 'a');
    }

    int q;
    cin >> q;
    while (q--) {
        string t;
        cin >> t;
        int p = 0;
        bool f = true;
        for (auto c : t) {
            if (!sam.t[p].next[c - 'a']) {
                f = false;
                break;
            } else {
                p = sam.t[p].next[c - 'a'];
            }
        }
        if (f) {
            cout << sam.t[p].fpos - t.length() + 2 << "\n";
        } else {
            cout << -1 << "\n";
        }
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // solve_SA();
    solve_SAM();

    return 0;
}