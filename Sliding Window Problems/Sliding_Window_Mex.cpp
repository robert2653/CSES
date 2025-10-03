#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    set<int> mex;
    // set<int> used;
    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i <= n; i++) {
        mex.insert(i);
    }
    vector<int> cnt(n);
    for (int r = 0; r < n; r++) {
        if (a[r] < n) {
            cnt[a[r]]++;
            // used.insert(a[r]);
            if (cnt[a[r]] == 1) {
                mex.erase(a[r]);
            }
        }
        if (r >= k && a[r - k] < n) {
            cnt[a[r - k]]--;
            if (cnt[a[r - k]] == 0) {
                // used.erase(a[r - k]);
                mex.insert(a[r - k]);
            }
        }
        if (r >= k - 1) {
            cout << *mex.begin() << " \n"[r == n - 1];
        }
    }
    return 0;
}