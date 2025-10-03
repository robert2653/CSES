#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Query { int id, l, r; };
void mo(vector<Query> &q) {
    int blk = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const Query &a, const Query &b) {
        int x = a.l / blk, y = b.l / blk;
        return x == y ? a.r < b.r : x < y;
    });
}
// struct Query { int l, r; };
// vector<int> mo(vector<Query> &q) {
//     int blk = sqrt(q.size());
//     vector<int> p(q.size());
//     iota(p.begin(), p.end(), 0);
//     sort(p.begin(), p.end(), [&](int a, int b) {
//         int x = q[a].l / blk, y = q[b].l / blk;
//         return x == y ? q[a].r < q[b].r : x < y;
//     });
//     return p;
// }

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> b = a;
    sort(b.begin(), b.end());
    b.resize(unique(b.begin(), b.end()) - b.begin());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(b.begin(), b.end(), a[i]) - b.begin();
    }

    vector<Query> qry;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        qry.push_back({i, l - 1, r});
    }
    mo(qry);

    vector<int> ans(q);
    int nl = 0, nr = 0;
    vector<int> rec(n);
    int now = 0;

    auto add = [&](int x) {
        if (!rec[x]) now++;
        rec[x]++;
    };
    auto del = [&](int x) {
        rec[x]--;
        if (!rec[x]) now--;
    };

    for (int i = 0; i < q; i++) {
        auto [id, l, r] = qry[i];
        while (nr < r) add(a[nr++]);
        while (r < nr) del(a[--nr]);
        while (nl < l) del(a[nl++]);
        while (l < nl) add(a[--nl]);
        ans[id] = now;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}