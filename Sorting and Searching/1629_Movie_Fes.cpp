#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
typedef pair<int, int> pii;
vector<pii> schedule;
#define all(x) (x).begin(), (x).end()
bool cmp(pii a, pii b){
    return a.second < b.second;
}
int main(){
    int ans = 0;
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        int st, end;
        cin >> st >> end;
        schedule.push_back({st, end});
    }
    sort(all(schedule), cmp);
    int now = 0;
    for(auto [st, end] : schedule){
        if(st >= now){
            ans++;
            now = end;
        }
    }
    cout << ans;
}