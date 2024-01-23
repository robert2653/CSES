#include <bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
int dep[maxn];
vector<int> tree[maxn];
int start, maxdep = 1;
void dfs(int par, int now){
    for(auto nxt : tree[now]){
        if(par != nxt){
            dep[nxt] = dep[now] + 1;
            if(dep[nxt] > maxdep){
                maxdep = dep[nxt];
                start = nxt;
            }
            dfs(now, nxt);
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
    dep[1] = 1;
    dfs(0, 1);
    dep[start] = 1;
    maxdep = 1;
    dfs(start, start);
    cout << maxdep - 1;
}