#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if ((i + j) % 2 == 0) {
                if (g[i][j] == 'A') {
                    g[i][j] = 'B';
                } else {
                    g[i][j] = 'A';
                }
            } else {
                if (g[i][j] == 'C') {
                    g[i][j] = 'D';
                } else {
                    g[i][j] = 'C';
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << g[i] << "\n";
    }
    return 0;
}