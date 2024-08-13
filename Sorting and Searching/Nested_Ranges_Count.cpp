#include <bits/stdc++.h>
using namespace std;
#define int long long
#define all(x) (x).begin(), (x).end()
struct BIT {    // BIT 都是 1-based 的查詢
    int n;
    vector<int> bit;
    BIT(int n) {    // 有幾個數
        this->n = n;
        bit.resize(n + 1, 0);
    }
    BIT(vector<int> &init) {    // 必須是 0-based
        this->n = init.size();
        bit.resize(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            modify(i, init[i - 1]);
        }
    }
    void modify(int i, int val) {
        for (; i <= n; i += i & -i) {
            bit[i] += val;
        }
    }
    int query(int r) {
	    int ans = 0;
	    for (; r; r -= r & -r) ans += bit[r];
	    return ans;
    }
    int query(int l, int r) {
        return query(r) - query(l - 1);
    }
};
signed main(){
    int n; cin >> n;
    vector<array<int, 3>> lines(n);
    vector<int> concrete(n);
    BIT containBIT(n), containedBIT(n);
    vector<int> contain(n), contained(n);
    for(int i = 0; i < n; i++){
        int u, v; cin >> u >> v;
        concrete[i] = v;
        lines[i] = {u, v, i};
    }
    sort(all(concrete));
    concrete.erase(unique(all(concrete)), concrete.end());
    for(int i = 0; i < n; i++){
        lines[i][1] = lower_bound(concrete.begin(), concrete.end(), lines[i][1]) - concrete.begin() + 1;
    }
    sort(all(lines), [](array<int, 3> &a, array<int, 3> &b) {
        if (a[0] == b[0]) return a[1] < b[1];
        return a[0] > b[0];
    });
    for (int i = 0; i < n; i++) {
        contain[lines[i][2]] = containBIT.query(lines[i][1]);
        containBIT.modify(lines[i][1], 1);
    }
    reverse(all(lines));
    for(int i = 0; i < n; i++){
        contained[lines[i][2]] = containedBIT.query(lines[i][1], n);
        containedBIT.modify(lines[i][1], 1);
    }
    for(int i = 0; i < n; i++){
        cout << contain[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < n; i++){
        cout << contained[i] << " ";
    }
}