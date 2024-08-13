#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll inf = 1E18;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n; 
    cin >> n;

    int a, b;
    cin >> a >> b;

    vector<ll> s(n + 1);
    deque<int> dq;

    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        s[i + 1] = s[i] + x;
        // cerr << s[i + 1] << " \n"[i == n - 1];
    }

    ll ans = -inf;

    for (int i = 0; i <= n - a; i++) {
        // cerr << i << ", ";
        while (!dq.empty() && dq.front() < i + a - b) {
            dq.pop_front();
        }
        ll add = s[i];
        while (!dq.empty() && s[dq.back()] > add) { // 要遞增
            dq.pop_back();
        }
        dq.push_back(i);
        ans = max(ans, s[i + a] - s[dq.front()]);
        // for (auto x : dq) cerr << x << " "; cerr << "\n";
    }

    cout << ans << "\n";

    return 0;
}