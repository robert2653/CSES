// 2D-BIT // Forest Queries (Area)
#include <bits/stdc++.h>
using namespace std;
using ll = long long;
int n;
int iiBIT[1005][1005], tree[1005][1005];
void modify(int x, int y, int mod){
    for(; x <= n; x += (x&-x)){
        for(int tmp = y; tmp <= n; tmp += (tmp&-tmp)){
            iiBIT[x][tmp] += mod;
        }
    }
}
ll query(int x1, int y1, int x2, int y2){
    ll ans = 0;
    x1--, y1--;
    int tmp1, tmp2;
    
    for(tmp1 = x2; tmp1; tmp1 -= (tmp1&-tmp1)){
        for(tmp2 = y2; tmp2; tmp2 -= tmp2&-tmp2){
            ans += iiBIT[tmp1][tmp2];
        }
    }
    for(tmp1 = x1; tmp1; tmp1 -= (tmp1&-tmp1)){
        for(tmp2 = y2; tmp2; tmp2 -= tmp2&-tmp2){
            ans -= iiBIT[tmp1][tmp2];
        }
    }
    for(tmp1 = x2; tmp1; tmp1 -= (tmp1&-tmp1)){
        for(tmp2 = y1; tmp2; tmp2 -= tmp2&-tmp2){
            ans -= iiBIT[tmp1][tmp2];
        }
    }
    for(tmp1 = x1; tmp1; tmp1 -= (tmp1&-tmp1)){
        for(tmp2 = y1; tmp2; tmp2 -= tmp2&-tmp2){
            ans += iiBIT[tmp1][tmp2];
        }
    }
    return ans;
}
int main(){
	ios::sync_with_stdio(0);
	cin.tie(nullptr);
	int q; 
	cin >> n >> q;
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            char t; cin >> t;
            if(t == '*'){
                modify(i, j, 1);
                tree[i][j]++;
            }
        }
    }
    for(int i = 1; i <= q; i++){
        int op; cin >> op;
        if(op == 1){
            int y, x; cin >> y >> x;
            int mod = tree[y][x] ? -1 : 1;
            tree[y][x] = !tree[y][x];
            modify(y, x, mod);
        }
        else {
            int y1, x1, y2, x2; cin >> y1 >> x1 >> y2 >> x2;
            cout << query(y1, x1, y2, x2) << "\n";
        }
            
    }
}