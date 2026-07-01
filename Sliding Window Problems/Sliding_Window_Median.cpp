#include <bits/stdc++.h>

using namespace std;
using ll = long long;

#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T> using pbds_set =
    tree<T, null_type, less<T>,
    rb_tree_tag, tree_order_statistics_node_update>;
template<class T> using pbds_multiset =
    tree<T, null_type, less_equal<T>,
    rb_tree_tag, tree_order_statistics_node_update>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    
    pbds_multiset<int> st;
    for (int i = 0; i < n; i++) {
        st.insert(a[i]);
        if (i >= k - 1) {
            cout << *st.find_by_order((k - 1) / 2) << " \n"[i == n - 1];
            st.erase(st.find_by_order(st.order_of_key(a[i - k + 1])));
        }
    }

    return 0;
}