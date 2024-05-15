#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n; cin >> n;
    deque<int> v(n);
    for(int i = 1; i <= n; i++){
        v[i - 1] = i;
    }
    while(!v.empty()){
        if(v.size() == 1){
            cout << v[0];
            return 0;
        }
        v.push_back(v[0]);
        v.pop_front();
        cout << v[0] << " ";
        v.pop_front();
    }
}