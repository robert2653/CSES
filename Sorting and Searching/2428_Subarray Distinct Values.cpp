#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define rep(i, st, n) for(int i = st; i < n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define pp pop()
#define tp top()
#define ph(x) push(x)
#define IO ios_base::sync_with_stdio(0); cin.tie();
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;
int k, n;
map<int, int> mp;
queue<int> q;
void solve(){
    int pre; cin >> pre; mp[pre]++; q.push(pre);
    ll ans = 1;
    int sum = 1;
    int now_size = 1;
    // cout << 1 << " ";
    rep(i, 1, n){   // 第i個往前數
        int now; cin >> now;
        if(mp[now] == 0) now_size++;
        mp[now]++;
        q.push(now);

        sum++;
        while(now_size > k){
            int tmp = q.front();
            q.pop();
            mp[tmp]--;
            sum--;
            if(mp[tmp] == 0) now_size--;
        }
        ans += sum;
        // cout << sum << " ";
    }
    cout << ans;
}
int main(){
    IO;
    cin >> n >> k;
    solve();
}