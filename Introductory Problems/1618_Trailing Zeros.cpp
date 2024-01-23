#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int ans = 0, n;
    cin >> n;
    for(long long i = 5; i <= 1000000000; i *= 5){
        if(i <= n){
            ans += n / i;
        }
        else break;
    }
    cout << ans;
}