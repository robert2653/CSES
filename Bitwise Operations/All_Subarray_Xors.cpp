#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void fwt(vector<ll> &a, bool inv = false) {
    // Or : [[1, 0], [1, 1]] -> [[1, 0], [-1, 1]]
    // And: [[1, 1], [0, 1]] -> [[1, -1], [0, 1]]
    // Xor: [[1, 1], [1, -1]] -> [[0.5, 0.5], [0.5, -0.5]]
    int n = __lg(int(a.size()));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 1 << n; ++j) {
            if (j >> i & 1) { // And
                ll x = a[j ^ (1 << i)];
                ll y = a[j];
                if (!inv) {
                    a[j ^ (1 << i)] = x + y;
                    a[j] = y;
                } else {
                    a[j ^ (1 << i)] = x - y;
                    a[j] = y;
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> pre(n + 1);
    set<int> st; st.insert(0);
    bool zero = false;
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] ^ a[i];
        if (st.find(pre[i + 1]) != st.end()) {
            zero = true;
        }
        st.insert(pre[i + 1]);
    }
    int m = __lg(*max_element(pre.begin(), pre.end())) + 1;

    vector<ll> A(1 << m);
    for (int i = 0; i <= n; i++) {
        A[pre[i]] = 1;
    }

    fwt(A, false);
    for (int i = 0; i < (1 << m); i++) {
        A[i] = A[i] * A[i];
    }
    fwt(A, true);

    vector<int> ans;
    if (zero) {
        ans.push_back(0);
    }
    for (int v = 1; v < (1 << m); v++) {
        if (A[v] > 0) {
            ans.push_back(v);
        }
    }
    cout << ans.size() << "\n";
    for (int i = 0; i < ans.size(); i++) {
        cout << ans[i] << " \n"[i + 1 == ans.size()];
    }
    return 0;
}