#include <bits/stdc++.h>
using namespace std;

template<class T, class F = less<T>>
struct RMQ { // [l, r)
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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    RMQ<int, greater<int>> rmq(a);
    map<int, set<int>> mp;
    for (int i = 0; i < n; i++) {
        mp[a[i]].insert(i);
    }
    auto divide = [&](auto self, int l, int r) -> int {
        if (l >= r) {
            return 0;
        }
        int mx = rmq(l, r);
        int ans = 0;
        int nl = l;
        auto it = mp[mx].lower_bound(nl);
        while (it != mp[mx].end() && *it <= r) {
            ans = max(ans, self(self, nl, *it));
            nl = (*it) + 1;
            it = next(it);
            if (it == mp[mx].end() || *it > r) {
                ans = max(ans, self(self, nl, r));
                break;
            }
        }
        return ans + 1;
    };
    cout << divide(divide, 0, n);
    return 0;
}