#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize ("03")
struct query {
    int l, r, id;
} typedef query;
void MO(int n, vector<query> &queries){
    int block = sqrt(n);
    function <bool(query, query)> cmp = [&](query a, query b) {
        int block_a = a.l / block;
        int block_b = b.l / block;
        if(block_a != block_b) return block_a < block_b;
        return a.r < b.r;
    };
    sort(queries.begin(), queries.end(), cmp);
}
void compress(vector<int> &nums){
    vector<int> sorted = nums;
    sort(sorted.begin(), sorted.end());
    unique(sorted.begin(), sorted.end());
    for(int i = 0; i < nums.size(); i++){
        nums[i] = lower_bound(sorted.begin(), sorted.end(), nums[i]) - sorted.begin() + 1;
    }
}

void add(int val, vector<int> &nums, vector<int> &record, int &distinct){
    record[val]++;;
    if(record[val] == 1) distinct++;
}
void remove(int val, vector<int> &nums, vector<int> &record, int &distinct){
    record[val]--;
    if(record[val] == 0) distinct--;
}
void solve(){
    int n, q; cin >> n >> q;
    vector<int> nums(n);
    vector<int> record(n + 1, 0);
    vector<query> queries(q);
    vector<int> ans(q);
    int distinct = 0;
    for(int i = 0; i < n; i++){
        cin >> nums[i];
    }
    compress(nums);
    for(int i = 0; i < q; i++){
        int l, r; cin >> l >> r;
        queries[i] = {l - 1, r - 1, i};
    }
    MO(n, queries);
    int cl = 1, cr = 0;
    for(auto [l, r, id] : queries){
        while (cl > l) {
            cl--;
            add(nums[cl], nums, record, distinct);
        }
        while (cr < r) {
            cr++;
            add(nums[cr], nums, record, distinct);
        }
        while (cl < l) {
            remove(nums[cl], nums, record, distinct);
            cl++;
        }
        while (cr > r) {
            remove(nums[cr], nums, record, distinct);
            cr--;
        }
        ans[id] = distinct;
    }
    for(auto &i : ans){
        cout << i << "\n";
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    solve();
}