#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<typename T>
struct Fenwick { // 全部以 0 based 使用
    int n; vector<T> a;
    Fenwick(int n_ = 0) { init(n_); }
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
    int select(const T &k, int start = 0) {
        // 找到最小的 x, 使得 sum(x + 1) - sum(start) > k
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
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 3>> a(n);
    vector<int> x;
    for (int i = 0; i < n; i++) {
        int l, r;
        cin >> l >> r;
        l--, r--;
        x.push_back(l);
        a[i] = {l, r, i};
    }
    sort(x.begin(), x.end());
    x.resize(unique(x.begin(), x.end()) - x.begin());
    int m = x.size();
    for (auto &[l, r, i] : a) {
        l = lower_bound(x.begin(), x.end(), l) - x.begin();
    }

    Fenwick<int> f1(m), f2(m);
    // 2 4
    // 3 6
    // 1 6
    // 4 8
    // 幾個 l 比當前大
    vector<int> ans1(n), ans2(n);
    sort(a.begin(), a.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[1] == b[1] ? a[0] > b[0] : a[1] < b[1];
    });
    for (int i = 0; i < n; i++) {
        auto [l, r, id] = a[i];
        ans1[id] = f1.rangeSum(l, m);
        f1.add(l, 1);
    }
    // 4 8
    // 1 6
    // 3 6
    // 2 4
    // 幾個 l 比當前小
    sort(a.begin(), a.end(), [](const array<int, 3> &a, const array<int, 3> &b) {
        return a[1] == b[1] ? a[0] < b[0] : a[1] > b[1];
    });
    for (int i = 0; i < n; i++) {
        auto [l, r, id] = a[i];
        ans2[id] = f2.rangeSum(0, l + 1);
        f2.add(l, 1);
    }
    for (int i = 0; i < n; i++) {
        cout << ans1[i] << " \n"[i == n - 1];
    }
    for (int i = 0; i < n; i++) {
        cout << ans2[i] << " \n"[i == n - 1];
    }

    return 0;
}