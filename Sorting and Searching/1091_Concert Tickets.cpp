#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m; cin >> n >> m;
    multiset<int> tik;
    for(int i = 0; i < n; i++){
        int tmp; cin >> tmp;
        tik.insert(tmp);
    }
    while(m--){
        int x; cin >> x;
        auto it = tik.upper_bound(x);
        if(it == tik.begin()){
            cout << -1 << " ";
            continue;
        }
        it--;
        cout << *it << " ";
        tik.erase(it);
    }
}