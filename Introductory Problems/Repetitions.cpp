#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int ans = 1;
    char c; cin >> c;
    char pre = c;
    int now = 1;
    while(cin >> c){
        if(c == pre) now++;
        else {
            now = 1;
            pre = c;
        }
        ans = max(ans, now);
    }
    cout << ans;
}