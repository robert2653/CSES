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
void solve(){
    int n; int L, R; cin >> n >> L >> R;
    vector<int> prefix(n + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        prefix[i + 1] = prefix[i] + x;
    }
    int ans = -llinf;
    // 使用 sliding window, ans[now] = pref[now] - min([pref[l, r]]), l = now - R, r = now - L;
    pbds_multiset<int> st;
    for (int now = L; now <= n; now++) {
        st.insert(prefix[now - L]);
        if (now - R - 1 >= 0) st.erase(st.upper_bound(prefix[now - R - 1]));
        ans = max(ans, prefix[now] - *st.begin());
        // cout << now << " ";
        // for (auto i : st) cout << i << " ";
        // cout << endl;
    }
    cout << ans << endl;
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