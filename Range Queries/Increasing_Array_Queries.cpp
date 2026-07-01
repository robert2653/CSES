#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

template<class T> struct Fenwick {
    int n; vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i)
            a[i - 1] = a[i - 1] + v;
    }
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i)
            ans = ans + a[i - 1];
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k, int start = 0) {
        // 找到最小的 x, 使得 sum(x + 1) - sum(start) > k
        // prefix sum 要有單調性
        int x = 0; T cur = -sum(start);
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<ll> pre(n + 1);
    for (int i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] + a[i - 1];
    }
    vector<vector<pair<int, int>>> qry(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        qry[l].emplace_back(r, i);
    }

    Fenwick<ll> f(n);
    vector<ll> ans(q);
    vector<int> stk {n};
    const int inf = 1E9;
    a.push_back(inf);
    vector<ll> contribute(n); // 當前當最小值，往右數到第一個比他大的位置時，對答案的貢獻
    for (int i = n - 1; i >= 0; i--) {
        int x = a[i];
        while (a[stk.back()] < x) {
            int p = stk.back();
            stk.pop_back();
            f.add(p, -contribute[p]);
        }
        contribute[i] = 1LL * (stk.back() - i) * a[i] - (pre[stk.back()] - pre[i]);
        f.add(i, contribute[i]);
        stk.push_back(i);
        for (auto &[r, id] : qry[i]) {
            auto it = lower_bound(stk.begin(), stk.end(), r, greater<int>());
            // 找到 stk 第一個 <= r 的位置 (stk 遞減)
            int p = *it;
            ans[id] = f.rangeSum(i, p) + 1LL * (r - p + 1) * a[p] - (pre[r + 1] - pre[p]);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}