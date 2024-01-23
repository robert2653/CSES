#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
int dp[1005][100005];
vector<int> Page(1005, 0);
vector<int> Price(1005, 0);
int main(){
    ios_base::sync_with_stdio();
    cin.tie();
    int n, bud;
    cin >> n >> bud;
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        Price[i] = tmp;
    }
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        Page[i] = tmp;
    }
    memset(dp, 0, sizeof(dp));
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= bud; j++){
            if(j >= Price[i]){
                dp[i][j] = max(dp[i-1][j], dp[i-1][j-Price[i]]+Page[i]);
            }
            else {
                dp[i][j] = dp[i-1][j];
            }
        }
    }
    cout << dp[n][bud] << endl;
    // for(int i = 0; i <= n; i++){
    //     for(int j = 0; j <= bud; j++){
    //         cout << dp[i][j] << " ";
    //     }
    // }
}