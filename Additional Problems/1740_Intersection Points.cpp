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
    constexpr int N = 2e6;
    int n; cin >> n;
    Fenwick<int> a(N + 1);
    struct Line {
        int x, y1, y2;
        int op; // 0 -1, 1 + 1, 2 query
        Line(int x_, int y1_, int y2_, int op_) : x(x_), y1(y1_), y2(y2_), op(op_) {}
        bool operator<(const Line &rhs) {
            return x == rhs.x ? op < rhs.op : x < rhs.x;
        }
    };
    vector<Line> e;
    for (int i = 0; i < n; i++) {
        int x1, x2, y1, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        // if (x1 > x2) {
        //     swap(x1, x2);
        // }
        // if (y1 > y2) {
        //     swap(y1, y2);
        // }
        x1 += N / 2;
        x2 += N / 2;
        y1 += N / 2;
        y2 += N / 2;
        if (x1 == x2) { // query
            e.push_back(Line(x1, y1, y2, 2));
        } else {
            e.push_back(Line(x1, y1, y2, 1));
            e.push_back(Line(x2 + 1, y1, y2, -1));
        }
    }
    sort(e.begin(), e.end());
    ll ans = 0;
    for (auto &l : e) {
        if (l.op == 2) {
            ans += a.rangeSum(l.y1, l.y2 + 1);
        } else {
            a.add(l.y1, l.op);
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
}