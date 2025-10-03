#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    string ans;
    ans.push_back(g[0][0]);
    vector<int> v {0};
    for (int j = 1; j < n; j++) {
        vector<int> nv;
        char mnc = 127;
        for (auto i : v) {
            mnc = min({mnc, g[i][j - i], g[i + 1][j - i - 1]});
        }
        for (auto i : v) {
            if (g[i][j - i] == mnc && (nv.empty() || nv.back() != i)) {
                nv.push_back(i);
            }
            if (g[i + 1][j - i - 1] == mnc) {
                nv.push_back(i + 1);
            }
        }
        swap(v, nv);
        ans.push_back(mnc);
    }
    for (int j = n; j < n * 2 - 1; j++) {
        vector<int> nv;
        char mnc = 127;
        for (auto i : v) {
            if (i > 0 && j - i < n) {
                mnc = min(mnc, g[i][j - i]); // right
            }
            if (i + 1 < n && j - i - 1 < n) { // down
                mnc = min({mnc, g[i + 1][j - i - 1]});
            }
        }
        for (auto i : v) {
            if (i > 0 && j - i < n && g[i][j - i] == mnc && (nv.empty() || nv.back() != i)) {
                nv.push_back(i);
            }
            if (i + 1 < n && j - i - 1 < n && g[i + 1][j - i - 1] == mnc) {
                nv.push_back(i + 1);
            }
        }
        swap(v, nv);
        ans.push_back(mnc);
    }
    cout << ans << "\n";
    return 0;
}