#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    long long n; cin >> n;
    for(long long i = 1; i <= n; i++){
        cout << (i * i) * (i * i - 1) / 2 << "\n";
    }
}