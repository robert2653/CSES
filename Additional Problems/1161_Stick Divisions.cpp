#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    priority_queue<int, vector<int>, greater<int>> pq;
    ll sum = 0;
    int _, n; cin >> _ >> n;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        pq.push(x);
    }
    while (pq.size() > 1) {
        int x = pq.top(); pq.pop();
        int y = pq.top(); pq.pop();
        sum += x + y;
        pq.push(x + y);
    }
    cout << sum << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}