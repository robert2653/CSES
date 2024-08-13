#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e5 + 5;

typedef struct {
    int set_val; int sum; int add;
} node;
int n, q; 
vector<node> tree;
vector<int> nums;
// Pull
void pull(int now){  // update now with 2 children
    tree[now].sum = tree[2 * now].sum + tree[2 * now + 1].sum;
}
// Lazy
void push(int now, int l, int r){
    if(tree[now].set_val){
        tree[now].sum = (r - l + 1) * tree[now].set_val;
    }
    tree[now].sum += (r - l + 1) * tree[now].add;
    if(l != r){
        if(tree[now].set_val){
            tree[2 * now].set_val = tree[now].set_val;
            tree[2 * now + 1].set_val = tree[now].set_val;
            tree[2 * now].add = tree[now].add;
            tree[2 * now + 1].add = tree[now].add;
        }
        else {
            tree[2 * now].add += tree[now].add;
            tree[2 * now + 1].add += tree[now].add;
        }
    }
    tree[now].add = 0; tree[now].set_val = 0;
}
// Build
void build(int L, int R, int now){
    if(L == R){
        tree[now].sum = nums[L];
        tree[now].set_val = tree[now].add = 0;
        return;
    }
    int M = (L + R) >> 1;
    build(L, M, now * 2);
    build(M + 1, R, now * 2 + 1);
    pull(now);
}
// modify
void modify_add(int l, int r, int L, int R, int now, int add){
    if(R < l || r < L) // invalid range
        return;
    if(l <= L && R <= r){
        tree[now].add += add;
        return;
    }
    push(now, L, R);
    int M = (L + R) >> 1;
    modify_add(l, r, L, M, now * 2, add);
    modify_add(l, r, M + 1, R, now * 2 + 1, add);
    push(now * 2, L, M);
    push(now * 2 + 1, M + 1, R);
    pull(now);  // update now with 2 children
}
void modify_set(int l, int r, int L, int R, int now, int val){
    if(R < l || r < L) // invalid range
        return;
    if(l <= L && R <= r){
        tree[now].set_val = val;
        tree[now].add = 0;
        return;
    }
    push(now, L, R);
    int M = (L + R) >> 1;
    modify_set(l, r, L, M, now * 2, val);
    modify_set(l, r, M + 1, R, now * 2 + 1, val);
    push(now * 2, L, M);
    push(now * 2 + 1, M + 1, R);
    pull(now);  // update now with 2 children
}
// query
int query(int l, int r, int L, int R, int now){
    int M = (L + R) >> 1;
    if(R < l || r < L){
        return 0;
    }
    push(now, L, R);
    if(l <= L && R <= r){
        return tree[now].sum;
    }
	return query(l, r, L, M, now * 2) + query(l, r, M + 1, R, now * 2 + 1);
}
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0);
    int q; cin >> n >> q;
    tree.resize(4 * n + 1);
    nums.resize(n + 1);
    for(int i = 1; i <= n; i++){
        cin >> nums[i];
    }
    build(1, n, 1);
    for(int i = 1; i <= q; i++){
        int op; cin >> op;
        if(op == 1){
            int a, b, val; cin >> a >> b >> val;
            modify_add(a, b, 1, n, 1, val);
        }
        else if(op == 2){
            int a, b, val; cin >> a >> b >> val;
            modify_set(a, b, 1, n, 1, val);
        }
        else {
            int a, b; cin >> a >> b;
            cout << query(a, b, 1, n, 1) << endl;
        }
    }
}