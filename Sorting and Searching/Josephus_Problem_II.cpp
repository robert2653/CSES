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
    int select(const T &k) { // 找到最小的 x, 使得 sum(x) >= k
        int x = 0;
        T cur{};
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] < k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

int main() {
    int n, k;
    cin >> n >> k;
    k--;
    Fenwick<int> bit(n);
    for (int i = 0; i < n; i++) {
        bit.add(i, 1);
    }
    int p = 1;
    int cnt = n;
    for (int i = 0; i < n; i++) {
        p = (p + k) % cnt + 1;
        int x = bit.select(p);
        bit.add(x, -1);
        cout << x + 1 << " ";
        cnt--;
    }

    return 0;
}