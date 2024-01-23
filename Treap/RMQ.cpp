#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define lrep(i, st, n) for(int i = st; i < n; i++)
#define rep(i, st, n) for(int i = st; i <= n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define init(x) memset(x, 0, sizeof(x));
#define lp 2*now
#define rp 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;

struct Treap {
    Treap *l, *r;
    int pri, subsize, val, mn;
    Treap(int _val){
        mn = val = _val;
        pri = rand();
        l = r = nullptr;
        subsize = 1;
    }
    void pull(){
        mn = val;
        subsize = 1;
        for(auto i: {l,r}){
            if(i){
                subsize += i->subsize;
                mn = min(mn, i->mn);
            }
        }
    }
};
int size(Treap *treap) {
    if (treap == NULL) return 0;
    return treap->subsize;
}
Treap *merge(Treap *a, Treap *b){
    if(!a || !b) return a ? a : b;
    if(a->pri <= b->pri){
        a->r = merge(a->r, b);
        a->pull();
        return a;
    }
    else {
        b->l = merge(a, b->l);
        b->pull();
        return b;
    }
}
// void split(Treap *t, int k, Treap *&a, Treap *&b){
//     if(!t) a = b = nullptr;
//     else if(size(t->l) < k){  // 
//         a = t;
//         split(t->r, k-size(t->l)-1, a->r, b);
//         a->pull();
//     }
//     else {
//         b = t;
//         split(t->l, k, a, b->l);
//         b->pull();
//     }
// }
pair<Treap*, Treap*> split(Treap *root, int k) {
	if (root == nullptr) return {nullptr, nullptr};
	if (size(root->l) < k) {
		auto [a, b] = split(root->r, k - size(root->l) - 1);
		root->r = a;
		root->pull();
		return {root, b};
	} else {
		auto [a, b] = split(root->l, k);
		root->l = b;
		root->pull();
		return {a, root};
	}
}
void solve(){
    int n, m; cin >> n >> m;
    Treap *root = nullptr;
    rep(i, 1, n){
        int val; cin >> val;
        root = merge(root, new Treap(val));
    }
    rep(i, 1, m){
        int op; cin >> op;
        if(op == 1){
            int k, x; cin >> k >> x;
            auto [a, b] = split(root, k-1);
            auto [c, d] = split(b, 1);
            c->val = c->mn = x;
            root = merge(a, merge(c, d));
        }
        else {
            int l, r; cin >> l >> r;
            auto [a, b] = split(root, l-1);
            auto [c, d] = split(b, r-l+1);
            cout << c->mn << endl;
            root = merge(a, merge(c, d));
        }
    }
}
int main(){
    IO;
    solve();
}