// #include <bits/stdc++.h>
// using namespace std;
// int main(){
//     ios::sync_with_stdio(0);
//     cin.tie(nullptr);
//     int n, k; cin >> n >> k;
//     vector<int> chi(n);
//     for(int i = 0; i < n; i++){
//         cin >> chi[i];
//     }
//     sort(chi.begin(), chi.end());
//     int ans = 0;
//     vector<bool> used(n, 0);
//     int l = 0, r = n - 1;
//     while(l <= r){
//         if(chi[l] + chi[r] <= k){
//             used[l] = used[r] = 1;
//             l++, r--, ans++;
//         }
//         else r--;
//     }
//     for(int i = 0; i < n; i++) {
//         if(!used[i]) ans++;
//     }
//     cout << ans;
// }
#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, k; cin >> n >> k;
    multiset<int> chi;
    for(int i = 0; i < n; i++){
        int tmp; cin >> tmp;
        chi.insert(tmp);
    }
    int ans = 0;
    while(!chi.empty()){
        ans++;
        auto End = --chi.end();   
        int x = *End;
        chi.erase(End);
        if(chi.empty()) break;
        auto it = chi.upper_bound(k - x);
        if(it == chi.begin()) continue;
        it--;
        if(*it + x <= k){
            chi.erase(it);
        }
    }
    cout << ans;
}