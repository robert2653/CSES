#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
using namespace std;
const int mod = 1e9 + 7;

// duval_algorithm
// 將字串分解成若干個非嚴格遞減的非嚴格遞增字串
// vector<string> duval(string s) {
//     int i = 0, n = s.size();
//     vector<string> res;
//     while (i < n) {
//         int k = i, j = i + 1;
//         while (s[k] <= s[j] && j < n) {
//             if (s[k] < s[j]) k = i;
//             else k++;
//             j++;
//         }
//         while (i <= k) {
//             res.push_back(s.substr(i, j - k));
//             i += j - k;
//         }
//     }
//     return res;
// }

// 最小旋轉字串
// string min_round(string s) {
//     s += s;
//     int i = 0, n = s.size();
//     int start = i;
//     while (i < n / 2) {
//         start = i;
//         int k = i, j = i + 1;
//         while (s[k] <= s[j] && j < n) {
//             if (s[k] < s[j]) k = i;
//             else k++;
//             j++;
//         }
//         while (i <= k) {
//             i += j - k;
//         }
//     }
//     return s.substr(start, n / 2);
// }

// void solve() {
//     string s; cin >> s;
//     cout << min_round(s);
// }

struct SAM {
    // 1 -> initial state
    static constexpr int ALPHABET_SIZE = 26;
    // node -> strings with the same endpos set
    // link -> longest suffix with different endpos set
    // len  -> state's longest suffix
    // fpos -> first endpos
    // range [len(link) + 1, len], (before return cur)
    struct Node {
        int len, link, fpos;
        array<int, ALPHABET_SIZE> next;
        Node() : len{}, link{}, fpos{}, next{} {}
    };
    vector<Node> t;
    SAM() { init(); }
    void init() {
        t.assign(2, Node());
        t[0].len = -1;
    }
    int newNode() {
        t.emplace_back();
        return t.size() - 1;
    }
    int extend(int p, int c) {
        if (!p) t[p].next[c] = 1;
        if (t[p].next[c]) {
            int q = t[p].next[c];
            if (t[q].len == t[p].len + 1) {
                return q;
            }
            int r = newNode();
            t[r].len = t[p].len + 1;
            t[r].link = t[q].link;
            t[r].next = t[q].next;
            t[r].fpos = t[q].fpos;
            t[q].link = r;
            while (t[p].next[c] == q) {
                t[p].next[c] = r;
                p = t[p].link;
            }
            return r;
        }
        int cur = newNode();
        t[cur].len = t[p].len + 1;
        t[cur].fpos = t[p].len;
        while (!t[p].next[c]) {
            t[p].next[c] = cur;
            p = t[p].link;
        }
        t[cur].link = extend(p, c);
        return cur;
    }
};
void solve() {
    SAM sam;
    string s;
    cin >> s;
    int n = s.length();
    s += s;
    vector<int> last(n * 2 + 1);
    last[0] = 1;
    for (int i = 0; i < n * 2; i++) {
        last[i + 1] = sam.extend(last[i], s[i] - 'a');
    }
    string ans;
    for (int i = 0, now = 1; i < n; i++) {
        for (int j = 0; j < SAM::ALPHABET_SIZE; j++) {
            if (sam.t[now].next[j]) {
                ans += 'a' + j;
                now = sam.t[now].next[j];
                break;
            }
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