#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace std;
#define int long long
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    __gnu_pbds::tree<int, __gnu_pbds::null_type, less<int>, __gnu_pbds::rb_tree_tag, __gnu_pbds::tree_order_statistics_node_update> pbds;
    int n, x; cin >> n >> x;
    for(int i = 1; i <= n; i++) pbds.insert(i);
    auto it = pbds.find_by_order(x % n);
    while(pbds.size() > 1){
        cout << *it << " ";
        // erase
        auto tmp = it;
        it++;
        pbds.erase(tmp);
        // update
        int now = pbds.order_of_key(*it);
        it = pbds.find_by_order((now + x) % pbds.size());
    }
    cout << *pbds.begin();
}