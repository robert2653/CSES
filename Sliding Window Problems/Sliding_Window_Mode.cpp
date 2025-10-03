#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    set<pair<int, int>> st;
    map<int, int> cnt;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int r = 0; r < n; r++) {
        cnt[a[r]]++;
        st.insert({cnt[a[r]], -a[r]});
        if (r >= k) {
            cnt[a[r - k]]--;
            st.erase({cnt[a[r - k]] + 1, -a[r - k]});
            st.insert({cnt[a[r - k]], -a[r - k]});
        }
        if (r >= k - 1) {
            cout << -st.rbegin()->second << " \n"[r == n - 1];
        }
    }
    return 0;
}