#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <typename T>
struct Fenwick { // 全部以 0 based 使用
    int n;
    vector<T> a;
    Fenwick(int n_ = 0) {
        init(n_);
    }
    void init(int n_) {
        n = n_;
        a.assign(n, T{});
    }
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] = a[i - 1] + v;
        }
    }
    T sum(int x) { // 左閉右開查詢
        T ans{};
        for (int i = x; i > 0; i -= i & -i) {
            ans = ans + a[i - 1];
        }
        return ans;
    }
    T rangeSum(int l, int r) { // 左閉右開查詢
        return sum(r) - sum(l);
    }
    int select(const T &k) { // 找到最小的 x, 使得 sum(x) > k
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

void solve() {
    int n;
    cin >> n;
    vector<pair<int, int>> a(n);
    Fenwick<int> f(n);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[i] = { x, i };
        f.add(i, 1);
    }
    sort(a.begin(), a.end(), greater<pair<int, int>>());

    ll ans = 0;
    for (auto [x, id] : a) {
        ans += min(f.sum(id), f.rangeSum(id + 1, n));
        f.add(id, -1);
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
}