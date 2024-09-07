#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct query {
    int l, r, id;
};
void Mo(vector<query> &q) {
    int block = sqrt(q.size());
    sort(q.begin(), q.end(), [&](const query &a, const query &b) {
        int x = a.l / block;
        int y = b.l / block;
        if (x != y) return x < y;
        return a.r < b.r;
    });
}

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

    vector<query> qry;
    for (int i = 0; i < q; i++) {
        int l, r;
        cin >> l >> r;
        qry.push_back({l - 1, r, i});
    }
    Mo(qry);

    vector<int> ans(q);
    int nl = 0, nr = 0;
    vector<int> rec(n);
    int now = 0;

    for (auto [l, r, id] : qry) {
        while (nl > l) {
            nl--;
            if (!rec[a[nl]]) now++;
            rec[a[nl]]++;
        }
        while (nl < l) {
            rec[a[nl]]--;
            if (!rec[a[nl]]) now--;
            nl++;
        }
        while (nr > r) {
            nr--;
            rec[a[nr]]--;
            if (!rec[a[nr]]) now--;
        }
        while (nr < r) {
            if (!rec[a[nr]]) now++;
            rec[a[nr]]++;
            nr++;
        }
        ans[id] = now;
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}