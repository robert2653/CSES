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
    Fenwick<int> fenwick(n);
    vector<vector<pair<int, int>>> qry(n);
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        qry[l].emplace_back(r, i);
    }
    vector<int> ans(q);
    vector<int> stk;
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && a[stk.back()] <= a[i]) {
            fenwick.add(stk.back(), -1);
            stk.pop_back();
        }
        fenwick.add(i, 1);
        stk.push_back(i);
        for (auto [r, id] : qry[i]) {
            ans[id] = fenwick.rangeSum(i, r + 1);
        }
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }

    return 0;
}