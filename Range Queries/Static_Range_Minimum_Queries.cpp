#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class T, class F = less<T>> struct RMQ { // [l, r)
    int n;
    F cmp = F();
    vector<vector<T>> g;
    RMQ() {}
    RMQ(const vector<T> &a, F cmp = F()) : cmp(cmp) {
        init(a);
    }
    void init(const vector<T> &a) {
        n = a.size();
        int lg = __lg(n);
        g.resize(lg + 1);
        g[0] = a;
        for (int j = 1; j <= lg; j++) {
            g[j].resize(n - (1 << j) + 1);
            for (int i = 0; i <= n - (1 << j); i++)
                g[j][i] = min(g[j - 1][i], g[j - 1][i + (1 << (j - 1))], cmp);
        }
    }
    T operator()(int l, int r) {
        assert(0 <= l && l < r && r <= n);
        int lg = __lg(r - l);
        return min(g[lg][l], g[lg][r - (1 << lg)], cmp);
    }
};

template<class T> struct ZKW {
    int n;
    vector<T> a;
    ZKW(int n) : n(n), a(2 * n) {}
    ZKW(const vector<T> &v) : n(v.size()), a(2 * n) {
        for (int i = 0; i < n; i++) a[i + n] = v[i];
        for (int i = n - 1; i > 0; i--) a[i] = a[i * 2] + a[i * 2 + 1];
    }
    void modify(int x, const T &i) {
        a[x += n] = i;
        for (int i = x / 2; i; i /= 2) a[i] = a[i * 2] + a[i * 2 + 1];
    }
    T query(int l, int r) {
        T x{}, y{};
        for (l += n, r += n; l < r; l /= 2, r /= 2) {
            if (l & 1) x = x + a[l++];
            if (r & 1) y = a[--r] + y;
        }
        return x + y;
    }
};
struct Info {
    int mn = 1E9;
};
Info operator+(const Info &a, const Info &b) {
    return {min(a.mn, b.mn)};
}


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<Info> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i].mn;
    }
    ZKW<Info> rmq(a);
    while (q--) {
        int l, r;
        cin >> l >> r;
        cout << rmq.query(l - 1, r).mn << "\n";
    }

    return 0;
}