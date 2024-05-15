#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<int> a(n);
    int s = 0;
    for(int i = 0; i < n; i++){
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    for(int i = 0; i < n - 1; i++){
        s += a[i];
    }
    if(s < a.back()){
        s = a.back() * 2;
    }
    else s += a.back();
    cout << s << "\n";
}