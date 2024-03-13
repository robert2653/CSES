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
template<typename T>
using pbds_rev_multiset = tree<T, null_type, greater_equal<T>, rb_tree_tag, tree_order_statistics_node_update>;
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
void add(pbds_multiset<int> &min_set, pbds_rev_multiset<int> &max_set, int x){
    if(max_set.empty() && min_set.empty()){
        max_set.insert(x);
    }
    else if(*max_set.begin() >= x) max_set.insert(x);
    else min_set.insert(x);
}
void del(pbds_multiset<int> &min_set, pbds_rev_multiset<int> &max_set, int x){
    if(!min_set.empty() && min_set.find(x) != min_set.end()){
        min_set.erase(min_set.find(x));
    }
    else max_set.erase(max_set.upper_bound(x));
    // else max_set.erase(max_set.find(x));
}
void equalize(pbds_multiset<int> &min_set, pbds_rev_multiset<int> &max_set){
    while (max_set.size() >= min_set.size() + 2){
        min_set.insert(*max_set.begin());
        max_set.erase(max_set.begin());
    }
    while (max_set.size() < min_set.size()){
        max_set.insert(*min_set.begin());
        min_set.erase(min_set.begin());
    }
}
void solve(){
    int n, k; cin >> n >> k;
    pbds_multiset<int> min_set;
    pbds_rev_multiset<int> max_set;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    for(int i = 0; i < k; i++){
        add(min_set, max_set, v[i]);
        equalize(min_set, max_set);
    }
    cout << *max_set.begin() << " ";
    // for(auto i : max_set) cout << i << " ";
    // for(auto i : min_set) cout << i << " ";
    for(int l = 0, r = k; r < n; l++, r++){
        del(min_set, max_set, v[l]);
        add(min_set, max_set, v[r]);
        equalize(min_set, max_set);
        // for(auto i : max_set) cout << i << " ";
        // for(auto i : min_set) cout << i << " ";
        // cout << "\n";
        cout << *max_set.begin() << " ";
    }
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