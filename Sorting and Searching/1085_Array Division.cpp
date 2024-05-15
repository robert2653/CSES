#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
using namespace __gnu_pbds;
template<typename T>
using pbds_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template<typename T>
using pbds_multiset = tree<T, null_type, less_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
struct edge {
    int from; int to;
    int weight;
};
struct node {
    int sum;
};
const int llinf = 4e18;
const int inf = 2e9;
const int mod = 1e9 + 7;
const int maxn = 2e5 + 5;
bool check(vector<int> &v, int m, int k){
    k--;
    int now = 0;
    for(int i = 0; i < v.size(); i++){
        if(v[i] > m) return false;
        if(now + v[i] > m){
            now = v[i];
            k--;
        }
        else {
            now += v[i];
        }
        if(k < 0) return false;
    }
    return true;
}
void solve(){
    int n, k; cin >> n >> k;
    vector<int> v(n);
    int sum = 0;
    for(int i = 0; i < n; i++){
        cin >> v[i];
        sum += v[i];
    }
    int l = 1, r = sum;
    while(l <= r){
        int m = (l + r) / 2;
        if(check(v, m, k)){
            r = m - 1;
        }
        else l = m + 1;
    }
    cout << l << endl;
}
signed main(){
    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}