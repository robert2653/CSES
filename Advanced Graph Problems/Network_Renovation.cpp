#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 讓每個點的 deg > 1 即可，並且盡量以不同 subtree 之間連線
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> leafs;
    vector<vector<int>> g(n);
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    auto dfs = [&](auto self, int u, int p) -> void {
        for (auto v : g[u]) {
            if (v == p) continue;
            self(self, v, u);
        }
        if (g[u].size() == 1) {
            leafs.push_back(u);
        }
    };
    dfs(dfs, 0, -1);
    if (leafs.size() & 1) {
        leafs.push_back(leafs[0]);
    }
    cout << leafs.size() / 2 << "\n";
    for (int i = 0; i < leafs.size() / 2; i++) {
        cout << leafs[i] + 1 << " " << leafs[i + leafs.size() / 2] + 1 << "\n";
    }
    return 0;
}