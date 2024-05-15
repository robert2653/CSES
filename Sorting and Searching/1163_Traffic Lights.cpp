#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
using namespace __gnu_pbds;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    int x, n; cin >> x >> n;
    tree<int, null_type, less<int>, rb_tree_tag,
         tree_order_statistics_node_update> used;
    multiset<int> mts = {x};
    used.insert(0); used.insert(x);
    int ans = x + 1;
    while(n--){
        int light; cin >> light;
        int upper = *used.upper_bound(light);
        int lower = *(--used.lower_bound(light));
        mts.erase(mts.find(upper - lower));
        mts.insert(upper - light);
        mts.insert(light - lower);
        used.insert(light);
        ans = *mts.rbegin();
        cout << ans << " ";
    }
}