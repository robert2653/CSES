#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<int> basis;
    auto add = [&](vector<int> &basis, int x) {
        for (auto i : basis) {
            x = min(x, x ^ i);
        }
        if (x) basis.push_back(x);
    };
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        add(basis, x);
    }
    cout << (1 << basis.size()) << "\n";
    return 0;
}