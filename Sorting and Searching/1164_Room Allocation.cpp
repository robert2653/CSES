#include <bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
#define int long long
typedef struct {
    int u, v, id;
} cust;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<cust> custs(n);
    for(int i = 0; i < n; i++){
        cin >> custs[i].u >> custs[i].v;
        custs[i].id = i;
    }
    vector<int> ans(n);
    int mx = 0;
    sort(custs.begin(), custs.end(), [&](cust a, cust b){ 
        if(a.u == b.u) return a.v < b.v;
        return a.u < b.u; });
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> used;
    priority_queue<int, vector<int>, greater<int>> can;
    for(int i = 1; i <= n; i++) can.push(i);
    for(auto &i : custs){
        while(!used.empty() && used.top().first < i.u){
            can.push(used.top().second);
            used.pop();
        }
        ans[i.id] = can.top();
        mx = max(mx, ans[i.id]);
        used.push({i.v, can.top()});
        can.pop();
    }
    cout << mx << "\n";
    for(auto &i : ans) cout << i << " ";
}