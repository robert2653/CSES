#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n; cin >> n;
    vector<pair<int, int>> v;
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        v.push_back({tmp, i});
    }
    sort(v.begin(), v.end());
    int pre = n + 1;
    int ans = 0;
    for(auto &[x, nxt] : v){
        if(nxt < pre) ans++;    // 用Iq96
        pre = nxt;
    }
    cout << ans;
}