#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    while(n--){
        int a, b; cin >> a >> b;
        if(a < b) swap(a, b);
        if((a + b) % 3) cout << "NO\n";
        else if(a > 2 * b) cout << "NO\n";
        else cout << "YES\n";
    }
}