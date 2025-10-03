#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int lo = 1, hi = 1E9;
    while (lo < hi) {
        int x = (lo + hi) / 2;
        cout << "? " << x << endl;
        string res;
        cin >> res;
        if (res == "YES") {
            lo = x + 1;
        } else {
            hi = x;
        }
    }
    cout << "! " << lo << endl;
    return 0;
}