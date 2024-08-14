#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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
    string s; ll k;
    cin >> s >> k;

    int n = s.length();
    SAM sam;
    vector<int> last(n + 1);
    last[0] = 1;
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
    for (int i = sz - 1; i >= 0; i--) {
        for (int u : order[i]) {
            if (sam.t[u].link != -1) {
                cnt[sam.t[u].link] += cnt[u];
            }
        }
    }

    vector<ll> dp(sz, -1);
    auto dfs = [&](auto self, int u) -> void {
        dp[u] = cnt[u];
        for (int c = 0; c < SAM::ALPHABET_SIZE; c++) {
            int v = sam.t[u].next[c];
            if (v) {
                if (dp[v] == -1) self(self, v);
                dp[u] += dp[v];
            }
        }
    };
    dfs(dfs, 1); // a, ab, abc, b, bc, c

    string ans;
    int p = 1;
    while (k > 0) {
        for (int c = 0; c < SAM::ALPHABET_SIZE; c++) {
            int v = sam.t[p].next[c];
            if (v) {
                if (k > dp[v]) {
                    k -= dp[v];
                } else {
                    ans.push_back('a' + c);
                    k -= cnt[v];
                    p = v;
                    break;
                }
            }
        }
    }
    
    cout << ans << "\n";
}

int main() {
    // freopen("1.in", "r", stdin);
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}