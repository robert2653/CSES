#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    vector<int> ans;
    vector<vector<int>> g(n);
    vector<int> in(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        in[v]++;
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (in[i] == 0) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans.push_back(u + 1);
        for (int v : g[u]) {
            in[v]--;
            if (in[v] == 0) {
                q.push(v);
            }
        }
    }

    if (ans.size() == n) {
        for (int i : ans) {
            cout << i << " ";
        }
    } else {
        cout << "IMPOSSIBLE";
    }
    return 0;
}