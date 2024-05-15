#include <bits/stdc++.h>
using namespace std;
// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(nullptr);
//     int n, k; cin >> n >> k;
//     map<int, vector<int>> mp;
//     vector<int> v(n + 1);
//     for(int i = 1; i <= n; i++){
//         int tmp; cin >> tmp;
//         mp[tmp].push_back(i);
//         v[i] = tmp;
//     }
//     for(int i = 1; i <= n; i++){
//         for(auto &u : mp[k - v[i]]){
//             if(i != u){
//                 std::cout << i << " " << u;
//                 return 0;
//             }
//         }
//     }
//     std::cout << "IMPOSSIBLE";
// }
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    vector<pair<int, int>> v = {{0, 0}};
    for(int i = 1; i <= n; i++){
        int tmp; cin >> tmp;
        v.push_back({tmp, i});
    }
    sort(v.begin(), v.end());
    int l = 1, r = n;
    while(l < r){
        int sum = v[l].first + v[r].first;
        if(sum == k){
            cout << v[l].second << " " << v[r].second;
            return 0;
        }
        else if(sum < k) l++;
        else r--;
    }
    cout << "IMPOSSIBLE";
}