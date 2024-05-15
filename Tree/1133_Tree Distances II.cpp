#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int> tree[maxn];
vector<int> subtree(maxn, 1);
long long ans[maxn];
int n;
void dfs(int par, int now, int depth){
    ans[1] += depth;
    for(auto nxt : tree[now]){
        if(par != nxt) {
            dfs(now, nxt, depth + 1);
            subtree[now] += subtree[nxt];
        }
    }
}
void find_ans(int par, int now){
// 往下走，每個子節點距離 - 1，非子節點則 + 1
    for(auto nxt : tree[now]){
        if(par != nxt){
            ans[nxt] = ans[now] + (n - subtree[nxt]) - subtree[nxt];
            find_ans(now, nxt);
        }
    }
}
int main(){
    cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(0, 1, 0);
    find_ans(0, 1);
    for(int i = 1; i <= n; i++){
        cout << ans[i] << " ";
    }
}