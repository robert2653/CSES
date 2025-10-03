#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
using namespace std;
using ll = long long;

const int B = 29;
const int N = 200000 * (B + 1);
int tot = 0;
int trie[N][2], cnt[N]; // 01 trie
void reset() {
    tot = 0, fill_n(trie[0], 2, 0);
}
int newNode() {
    int x = ++tot;
    cnt[x] = 0, fill_n(trie[x], 2, 0);
    return x;
}
void add(int x) {
    int p = 0;
    for (int i = B; i >= 0; i--) {
        int &q = trie[p][x >> i & 1];
        if (!q) q = newNode();
        p = q;
    }
    cnt[p] += 1;
}
int find(int x) {
    int p = 0;
    int ans = 0;
    for (int i = B; i >= 0; i--) {
        int u = x >> i & 1;
        if (trie[p][u ^ 1]) {
            p = trie[p][u ^ 1];
            ans |= 1 << i;
        } else {
            p = trie[p][u];
        }
    }
    return ans;
}

void solve() {
    int n; cin >> n;
    vector<int> a(n);
    for (auto &x : a) {
        cin >> x;
    }

    int now = 0, ans = 0;
    add(now);
    for (int i = 0; i < n; i++) {
        now ^= a[i];
        add(now);

        ans = max(ans, find(now));
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