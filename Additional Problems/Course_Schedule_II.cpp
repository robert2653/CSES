#include <bits/stdc++.h>

using namespace std;
using ll = long long;

void solve() {
    int n, m;
    cin >> n >> m;
    priority_queue<int> pq;
    vector<int> in(n), vis(n);
    vector g(n, vector<int>());

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        swap(u, v);
        in[v]++;
        g[u].push_back(v);
    }
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            pq.push(i);
        }
    }

    vector<int> ans;

    while (!pq.empty()) {
        int u = pq.top();
        ans.push_back(u);
        pq.pop();
        for (int v : g[u]) {
            in[v]--;
            if (in[v] == 0) pq.push(v);
        }
    }

    reverse(ans.begin(), ans.end());
    for (auto i : ans) cout << i + 1 << " ";
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