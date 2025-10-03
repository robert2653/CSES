#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 1E7;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    const pair<int, int> nosol = {-1, -1};
    vector<pair<int, int>> v(N + 1, nosol);
    for (int i = 0; i * i <= N; i++) {
        for (int j = 0; i * i + j * j <= N; j++) {
            v[i * i + j * j] = {i, j};
        }
    }
    int t;
    cin >> t;
    while (t--) {
        int n;
        cin >> n;
        for (int i = 0; i <= n; i++) {
            if (v[i] != nosol && v[n - i] != nosol) {
                cout << v[i].first << " " << v[i].second << " " << v[n - i].first << " " << v[n - i].second << "\n";
                break;
            }
        }
    }
    return 0;
}