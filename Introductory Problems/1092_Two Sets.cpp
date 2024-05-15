#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    long long n; cin >> n;
    if(n * (n + 1) % 4){
        cout << "NO"; return 0;
    }
    cout << "YES\n";
    int l = 1, r = n;
    long long nokori = n * (n + 1) / 4;
    vector<bool> used(n + 1, 0);
    int cnt = 0;
    while(true){
        used[l] = 1;
        nokori -= l;
        l++; cnt++;
        if(nokori == 0) break;
        if(r >= nokori){
            used[nokori] = 1; cnt++;
            break;
        }
        used[r] = 1;
        nokori -= r;
        r--; cnt++;
    }
    cout << cnt << "\n";
    for(int i = 1; i <= n; i++){
        if(used[i]) cout << i << " ";
    }
    cout << "\n" << n - cnt << "\n";
    for(int i = 1; i <= n; i++){
        if(!used[i]) cout << i << " ";
    }
}