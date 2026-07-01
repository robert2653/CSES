#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

struct Query { int id, l, r; };
void mo(vector<Query> &q) {
    int blk = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const Query &a, const Query &b) {
        int x = a.l / blk, y = b.l / blk;
        return x == y ? a.r < b.r : x < y;
    });
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto s = a;
    ranges::sort(s);
    s.erase(unique(s.begin(), s.end()), s.end());

    for (auto &x : a) x = lower_bound(s.begin(), s.end(), x) - s.begin();

    vector<Query> qry(q);
    for (int i = 0; i < q; i++) {
        cin >> qry[i].l >> qry[i].r;
        qry[i].l--, qry[i].r--;
        qry[i].id = i;
    }
    mo(qry);

    int m = s.size();
    int nl = 0, nr = -1;
    vector<int> cnt(m);
    vector<int> ans(q);
    int cur = 0;
    auto addR = [&]() {
        int x = a[nr];
        if (cnt[x]++ == 0) cur++;
    };
    auto delR = [&]() {
        int x = a[nr];
        if (--cnt[x] == 0) cur--;
    };
    auto addL = [&]() {
        int x = a[nl];
        if (cnt[x]++ == 0) cur++;
    };
    auto delL = [&]() {
        int x = a[nl];
        if (--cnt[x] == 0) cur--;
    };

    for (auto [id, l, r] : qry) {
        while (nr < r) nr++, addR();
        while (l < nl) nl--, addL();
        while (r < nr) delR(), nr--;
        while (nl < l) delL(), nl++;
        ans[id] = cur;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    
    return 0;
}