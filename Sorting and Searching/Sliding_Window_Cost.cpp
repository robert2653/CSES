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
    if(!min_set.empty() && *min_set.upper_bound(x) == x){
        min_set.erase(min_set.upper_bound(x));
    }
    else max_set.erase(max_set.upper_bound(x));
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
    pbds_multiset<int> geq_mid_set;
    pbds_rev_multiset<int> le_mid_set;
    int geq_pref = 0, le_pref = 0;
    vector<int> v(n);
    for(int i = 0; i < n; i++){
        cin >> v[i];
    }
    for(int i = 0; i < k; i++){
        add(min_set, max_set, v[i]);
        equalize(min_set, max_set);
    }
    int mid = *max_set.begin();
    for(int i = 0; i < k; i++){
        if(v[i] >= mid) {
            geq_mid_set.insert(v[i]);
            geq_pref += v[i];
        }
        else {
            le_mid_set.insert(v[i]);
            le_pref += v[i];
        }
    }
    cout << geq_pref - geq_mid_set.size() * mid + le_mid_set.size() * mid - le_pref << " ";

    for(int l = 0, r = k; r < n; l++, r++){ // 刪掉 l 增加 r
        del(min_set, max_set, v[l]);
        add(min_set, max_set, v[r]);
        equalize(min_set, max_set);
        int nxt_mid = *max_set.begin();
        if(v[l] >= mid){
            geq_mid_set.erase(geq_mid_set.upper_bound(v[l]));
            geq_pref -= v[l];
        }
        else {
            le_mid_set.erase(le_mid_set.upper_bound(v[l]));
            le_pref -= v[l];
        }
        geq_mid_set.insert(v[r]);
        geq_pref += v[r];
        mid = nxt_mid;
        while(!geq_mid_set.empty() && *geq_mid_set.begin() < mid){
            auto it = geq_mid_set.begin();
            le_mid_set.insert(*it);
            le_pref += *it;
            geq_pref -= *it;
            geq_mid_set.erase(it);
        }
        while(!le_mid_set.empty() && *le_mid_set.begin() >= mid){
            auto it = le_mid_set.begin();
            geq_mid_set.insert(*it);
            geq_pref += *it;
            le_pref -= *it;
            le_mid_set.erase(it);
        }
        cout << geq_pref - geq_mid_set.size() * mid + le_mid_set.size() * mid - le_pref << " ";
    }
}
signed main(){
    // pbds_multiset 的 upper_bound 跟 lower_bound 功能相反, 如果要 find, 插入 inf 後使用 upper_bound
    // 內建 multiset 可以跟 set 一樣正常使用, 自定義比較結構就比照以上
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