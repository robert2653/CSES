#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

void solve_dp() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    a.insert(a.end(), a.begin(), a.end());
    vector<int> grp(n * 2);
    ll cur = 0;
    for (int i = 0, g = 1; i < 2 * n; i++) {
        cur += a[i];
        if (cur > k) {
            g++;
            cur = a[i];
        }
        grp[i] = g;
    }
    vector<int> dp(2 * n);
    int l = 0;
    cur = 0;
    int ans = grp[n - 1];
    // dp[i] 記錄了以第 i 個元素當結尾，往前一直分組，最後那一組的 index
    // 目標是找到一個位於 grp[0] 的 l 到 grp[ans] 的 r，讓他們的距離 >= n，同時可以分成 ans - 1 組
    for (int i = 0; i < 2 * n; i++) {
        if (grp[i] > ans) {
            break;
        }
        if (grp[i] == 1) {
            dp[i] = i;  // 前 i 個都不算進去解
            cur += a[i];
            continue;
        }
        cur += a[i];
        while (cur > k) {
            cur -= a[l++];
        }
        // 找到最極限的 l，讓 l 當開頭完成分組，因此 dp[l - 1] 可以轉移到 dp[i]
        dp[i] = dp[l - 1];
        if (i - dp[i] >= n) { // 完成目標
            assert(grp[dp[i]] == 1);
            assert(grp[i] == ans);
            ans--;
            break;
        }
    }
    cout << ans << "\n";
}

void solve() {
    int n;
    ll k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<pair<int, int>> len;
    ll cur = 0;
    for (int i = 0, l = 0; i < n; i++) {
        cur += a[i];
        if (cur > k) {
            len.emplace_back(l, i - 1);
            cur = a[i];
            l = 1;
        } else {
            l++;
        }
        if (i == n - 1) {
            len.emplace_back(l, i);
        }
    }
    // 如果只有一個段，答案直接是 1
    if (len.size() == 1) {
        cout << 1 << "\n";
        return;
    }
    // 找到連續的兩個段，其長度總和最小，拿這個兩個段枚舉開頭
    int mn = n + 1, p = -1;
    for (int i = 1; i < len.size(); i++) {
        if (len[i].first + len[i - 1].first < mn) {
            mn = len[i].first + len[i - 1].first;
            p = len[i].second;
        }
    }
    // [l, r]
    int l = p - mn + 1, r = p;
    a.insert(a.end(), a.begin(), a.end());
    vector<ll> pre(2 * n + 1);
    for (int i = 0; i < 2 * n; i++) {
        pre[i + 1] = pre[i] + a[i];
    }
    int ans = n;
    for (int i = l; i <= r; i++) {
        int cur = i;
        int cnt = 0;
        // 二分搜找到這個段的結尾 (idx, cur 0-based. pre 1-based)
        while (cur < i + n) {
            int idx = upper_bound(pre.begin() + cur + 1, pre.begin() + i + n + 1, pre[cur] + k) - pre.begin() - 1;
            cnt++;
            cur = idx;
        }
        chmin(ans, cnt);
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // auto s = chrono::high_resolution_clock::now();

    int t = 1;
    // cin >> t;
    while (t--) {
        // solve();
        solve_dp();
    }

    // auto e = chrono::high_resolution_clock::now();
    // cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    
    return 0;
}