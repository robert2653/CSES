#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    if(n == 1) {
        cout << 1; return 0;
    }
    if(n == 2 || n == 3){
        cout << "NO SOLUTION"; return 0;
    }
    int now = 2;
    while(now <= n){
        cout << now << " ";
        now += 2;
    }
    now = 1;
    while(now <= n){
        cout << now << " ";
        now += 2;
    }
}