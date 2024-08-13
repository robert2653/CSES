#include <bits/stdc++.h>
using namespace std;
#define int long long
signed main(){
    int n; cin >> n;
    vector<int> v(n);
    for(int i = 0; i < n; i++) cin >> v[i];
    set<int> st;
    int l = 0, r = -1;
    int mx = 0;
    while(r < n){
        while(r < n - 1 && st.find(v[r + 1]) == st.end()){
            st.insert(v[r + 1]);
            r++;
            mx = max(mx, r - l + 1);
        }
        if(r >= n - 1) break;
        while(true){
            st.erase(v[l]);
            l++;
            if(v[l - 1] == v[r + 1]) break;
        }
    }
    cout << mx;
}