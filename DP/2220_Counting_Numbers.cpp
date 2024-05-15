#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
ll dp[20][10];  // dp[i][j] = [10^i * j, 10^i * (j+1))
void make_chart(){
    memset(dp, 0, sizeof(dp));
    // memset(sum, 0, sizeof(sum));
    for(int i = 0; i <= 9; i++){
        dp[0][i] = 1;
    }
    dp[1][0] = 10; // 0~9

    for(int i = 1; i < 18; i++){
        for(int j = 1; j <= 9; j++){
            for(int k = 1; k <= 9; k++){
                dp[i][j] += dp[i-1][k];
            }
        }
        for(int k = 0; k <= 9; k++){
            dp[i+1][0] += dp[i][k];
        }
    }
    // for(int i = 0; i < 18; i++){
    //     for(int j = 0; j <= 9; j++){
    //         cout << dp[i][j] << " ";
    //     }
    //     cout << "\n";
    // }
}
bool valid(string s){
    int size = s.size();
    for(int i = 0; i < size-1; i++){
        if(s[i] == s[i+1]){
            return 0;
        }
    }
    return 1;
}
ll get_num(string x){
    //2543 = 0~(2000-1) + 2000~(2500-1) + 2500~(2540-1) + 2540~2543
    ll ans = 0;
    int n = x.size(); ll l = stoll(x);
    for(int i = 0; i < n; i++){
        string fr = x.substr(0, i);
        ll tmp = l / pow(10, n-i);
        tmp *= pow(10, n-i);

        if(valid(fr)){
            for(int j = 0; j < x[i]-'0'; j++){
                if(fr.back()-'0' == j) continue;
                ans += dp[n-i-1][j];
                if(i > 0 && j == 0 && i != n-1) ans -= dp[n-i-2][j];
                // 10X: +[0~9]-1; 12X: +[20~29]; (n=3, i=1)
                // 最大位跟個位都不用扣
            }    
        }
    }
    if(valid(x)) ans++;
    return ans;
}
int main(){
    ios_base::sync_with_stdio();
    cin.tie();
    make_chart();
    string a, b; cin >> a >> b;
    ll x, y;
    if(a == "0") x = 0;
    else x = get_num(to_string(stoll(a)-1));
    y = get_num(b);
    // cout << "x=" << x << " y=" << y << "\n";
    cout << y-x << endl;
}