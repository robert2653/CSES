#include <bits/stdc++.h>

using namespace std;
using ll = long long;

constexpr int inf = 1E9;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    unordered_map<string, int> dis;
    vector<pair<int, int>> swp {{0, 1}, {1, 2}, {3, 4}, {4, 5}, {6, 7}, {7, 8}};
    for (int i = 0; i < 6; i++) {
        swp.emplace_back(i, i + 3);
    }
    
    string t;
    for (int i = 0; i < 9; i++) {
        char c;
        cin >> c;
        t.push_back(c);
    }

    string s = "123456789";
    queue<string> q;
    q.push(s);
    dis[s] = 0;
    while (!q.empty()) {
        string u = q.front();
        q.pop();
        int d = dis[u];
        for (int i = 0; i < 12; i++) {
            swap(u[swp[i].first], u[swp[i].second]);
            if (!dis.count(u)) {
                dis[u] = d + 1;
                q.push(u);
            }
            swap(u[swp[i].first], u[swp[i].second]);
        }
    }

    cout << dis[t] << "\n";

    return 0;
}