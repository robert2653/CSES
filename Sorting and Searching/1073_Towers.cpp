#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    // monostack
    multiset<int> mono;
    int n; cin >> n;
    while(n--){
        int tmp; cin >> tmp;
        auto it = mono.upper_bound(tmp);
        if(it != mono.end()) mono.erase(it);
        mono.insert(tmp); 
    }
    cout << mono.size();
}