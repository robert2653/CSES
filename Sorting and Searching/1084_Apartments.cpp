#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int n, m, k; cin >> n >> m >> k;
    vector<int> ap(n), per(m);
    for(int i = 0; i < n; i++) cin >> ap[i];
    for(int i = 0; i < m; i++) cin >> per[i];
    sort(ap.begin(), ap.end());
    sort(per.begin(), per.end());
    int nowap = 0, nowper = 0;
    int ans = 0;
    while(nowap < n && nowper < m){
        if(abs(ap[nowap] - per[nowper]) <= k){
            ans++;
            nowap++;
            nowper++;
        }
        else if(ap[nowap] - per[nowper] > k){
            // per too small
            nowper++;
        }
        else {  // ap too small
            nowap++;
        }
    }
    cout << ans;
}