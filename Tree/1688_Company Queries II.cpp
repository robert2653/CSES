#include <bits/stdc++.h>
using namespace std;
// LCA 裸題
void cal_h(int par, int now, vector<int> &height, vector<vector<int>> &tree) {
    for (auto nxt : tree[now]) {
        if (nxt == par) continue;
        height[nxt] = height[now] + 1;
        cal_h(now, nxt, height, tree);
    }
}
int find_ancestor(int now, int k, vector<vector<int>> &boss_chart){
    for(int i = 0; i <= 17; i++){
        if(k & (1 << i)) now = boss_chart[now][i];
    }
    return now;
}
int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q; cin >> n >> q;
    vector<vector<int>> boss_chart(n + 1, vector<int>(18, -1));
    vector<int> height(n + 1);
    vector<vector<int>> tree(n + 1, vector<int>());
    boss_chart[1][0] = 1;
    for(int i = 2; i <= n; i++){
        int boss; cin >> boss;
        boss_chart[i][0] = boss;
        tree[i].push_back(boss);
        tree[boss].push_back(i);
    }
    for(int i = 1; i <= 17; i++){
        for(int j = 1; j <= n; j++){
            boss_chart[j][i] = boss_chart[boss_chart[j][i - 1]][i - 1];
        }
    }
    cal_h(1, 1, height, tree);
    while (q--) {
        int a, b; cin >> a >> b;
        if (height[a] < height[b]) swap(a, b);  // a > b
        a = find_ancestor(a, height[a] - height[b], boss_chart);
        if (a == b) {
            cout << a << "\n";
            continue;
        }
        for (int i = 17; i >= 0; i--) {
            if(boss_chart[a][i] != boss_chart[b][i]){ // if a, b up 2 ^ i not the same point
                a = boss_chart[a][i];
                b = boss_chart[b][i];
            }
        }
        cout << boss_chart[a][0] << "\n"; // more one
    }
}