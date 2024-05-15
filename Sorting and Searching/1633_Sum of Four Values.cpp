#include <bits/stdc++.h>
using namespace std;
#define int long long
#define pii pair<int, int>
signed main(){
    #ifdef LOCAL
    freopen("1.in", "r", stdin);
    freopen("1.ans", "w", stdout);
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    clock_t start = clock();
    int n, k; cin >> n >> k;
    vector<pair<int, int>> a(n);
    for(int i = 0; i < n; i++){
        cin >> a[i].first;
        a[i].second = i;
    }
    multimap<int, array<int, 2>> mp;
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            mp.insert(pair<int, array<int, 2>>(a[i].first + a[j].first, array<int, 2>({i, j})));
        }
    }
    for(auto now : mp){
        int tar = k - now.first;
        if(tar <= 0) break;
        int i = now.second[0], j = now.second[1];
        auto it = mp.lower_bound(tar);
        if(it == mp.end()) continue;
        auto nxt = ++it; it--;
        while(nxt != mp.end() && nxt->first == tar && (it->second[0] == i || it->second[0] == j || it->second[1] == i || it->second[1] == j)){
            it++; nxt++;
        }
        // cerr << i + 1 << " " << j + 1 << " " << it->second[0] + 1 << " " << it->second[1] + 1 << " " << it->first + (k - tar) << "\n";
        if(it->second[0] != i && it->second[0] != j && it->second[1] != i && it->second[1] != j && it->first == tar){
            cout << i + 1 << " " << j + 1 << " " << it->second[0] + 1 << " " << it->second[1] + 1 << "\n";
            return 0;
        }
    }
    cout << "IMPOSSIBLE";
    cerr << (clock() - start) / (double)CLOCKS_PER_SEC;
}