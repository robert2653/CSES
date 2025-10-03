#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class T>
struct Fenwick {
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

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto sorted = a;
    sort(sorted.begin(), sorted.end());
    sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());
    int m = sorted.size();

    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin();
    }

    Fenwick<int> f(m);
    ll ans = 0;
    for (int r = 0; r < n; r++) {
        f.add(a[r], 1);
        ans += f.rangeSum(a[r] + 1, m);
        if (r >= k) {
            f.add(a[r - k], -1);
            ans -= f.sum(a[r - k]);
        }
        if (r >= k - 1) {
            cout << ans << " \n"[r == n - 1];
        }
    }
    return 0;
}