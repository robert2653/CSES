#include <bits/stdc++.h>
using namespace std;
void solve(){
    long long x, y; cin >> x >> y;
    if(x >= y){
        if(x & 1) cout << (x - 1) * (x - 1) + y;
        else cout << x * x - y + 1;
    }
    else {
        if(y & 1) cout << y * y - x + 1;
        else cout << (y - 1) * (y - 1) + x;
    }
    cout << "\n";
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int tt; cin >> tt;
    while(tt--) solve();
}