#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
vector<int> tree[maxn];
vector<bool> used(maxn, 0);
int ans = 0;
void dfs(int par, int now){
    for(auto nxt : tree[now]){
        if(par != nxt){
            dfs(now, nxt);
            if(!used[now] && !used[nxt]){
                ans++;
                used[now] = used[nxt] = 1;
            }
        }
    }
}
int main(){
    int n; cin >> n;
    for(int i = 1; i < n; i++){
        int u, v; cin >> u >> v;
        tree[u].push_back(v);
        tree[v].push_back(u);
    }
    dfs(0, 1);
    cout << ans;
}