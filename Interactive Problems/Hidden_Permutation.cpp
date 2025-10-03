#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    auto ask = [](int l, int r) -> bool {
        cout << "? " << l + 1 << " " << r + 1 << endl;
        string res;
        cin >> res;
        return res == "YES";
    };
    auto merge = [&](int l, int m, int r) {
        int L = m - l + 1, R = r - m;
        int i = 0, j = 0;
        vector<int> vl(v.begin() + l, v.begin() + m + 1);
        vector<int> vr(v.begin() + m + 1, v.begin() + r + 1);
        while (i < L && j < R) {
            if (ask(vl[i], vr[j])) {
                v[l++] = vl[i++];
            } else {
                v[l++] = vr[j++];
            }
        }
        while (i < L) {
            v[l++] = vl[i++];
        }
        while (j < R) {
            v[l++] = vr[j++];
        }
    };
    auto mergeSort = [&](auto self, int l, int r) {
        if (r <= l) {
            return;
        }
        int m = (l + r) / 2;
        self(self, l, m);
        self(self, m + 1, r);
        merge(l, m, r);
    };
    mergeSort(mergeSort, 0, n - 1);
    cout << "! ";
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[v[i]] = i + 1;
    }
    for (int i = 0; i < n; i++) {
        if (i < n) {
            cout << ans[i] << " ";
        } else {
            cout << ans[i] << endl;
        }
    }
    return 0;
}