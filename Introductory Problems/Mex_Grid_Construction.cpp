#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<vector<int>> ans(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (i % 2 == 0) {
                ans[i][j] = i + j;
            } else {
                ans[i][j] = i - j;
            }
        }
    }
    for (int j = 0; j < n; j++) {
        for (int i = 0; i < j; i++) {
            if (j % 2 == 0) {
                ans[i][j] = j + i;
            } else {
                ans[i][j] = j - i;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << ans[i][j] << " \n"[j == n - 1];
        }
    }
    return 0;
}