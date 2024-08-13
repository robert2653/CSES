#include <bits/stdc++.h>
using namespace std;
int main(){
    int n, q; cin >> n >> q;
    vector<vector<int>> dp(n+1, vector<int>(18, -1));
    dp[1][0] = 1;
    for(int i = 2; i <= n; i++){
        cin >> dp[i][0];
    }
    for(int i = 1; i <= 17; i++){
        for(int j = 1; j <= n; j++){
            dp[j][i] = dp[dp[j][i-1]][i-1];
        }
    }
    while(q--){
        int x, k; cin >> x >> k;
        int xx = x, kk = k - 1;
        for(int i = 17; i >= 0; i--){
            if(k & (1 << i)){
                x = dp[x][i];
            }
        }
        for(int i = 17; i >= 0; i--){
            if(kk & (1 << i)){
                xx = dp[xx][i];
            }
        }
        if(xx == x){
            cout << -1 << "\n";
            continue;
        }
        cout << x << "\n";
    }
}