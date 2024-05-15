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
    int pri, subsize, val; bool rev_valid;
    ll sum;
    Treap(int _val){
        sum = val = _val;
        pri = rand();
        rev_valid = false;
        l = r = nullptr;
        subsize = 1;
    }
    void pull(){
        subsize = 1;
        sum = val;
        for(auto i: {l,r}){
            if(i){
                subsize += i->subsize;
                sum += i->sum; 
            }
        }
    }
};
void push(Treap *t){
    if(!t) return;
    if(t->rev_valid){
        swap(t->l, t->r);
        if(t->l) t->l->rev_valid ^= 1;
        if(t->r) t->r->rev_valid ^= 1;
    }
    t->rev_valid = false;
}
int size(Treap *treap) {
    if (treap == NULL) return 0;
    return treap->subsize;
}
Treap *merge(Treap *a, Treap *b){
    if(!a || !b) return a ? a : b;
    push(a); push(b);
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
pair<Treap*, Treap*> split(Treap *root, int k) {
	if (root == nullptr) return {nullptr, nullptr};
    push(root);
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
// void Print(Treap *t){
//     if(t){
//         push(t);
//         Print(t->l);
//         cout << t->val;
//         Print(t->r);
//     }
// }
void solve(){
    int n, m; cin >> n >> m;
    Treap *root = nullptr;
    rep(i, 1, n){
        int tmp; cin >> tmp;
        root = merge(root, new Treap(tmp));
    }
    rep(i, 1, m){
        int op; cin >> op;  // 1 for rev, 2 for query
        if(op == 1){
            int x, y; cin >> x >> y;
            if(x == y){
                // Print(root); 
                continue;
            }
            auto [a, b] = split(root, x-1);
            auto [c, d] = split(b, y-x+1);
            c->rev_valid ^= true;
            push(c);
            b = merge(c, d);
            root = merge(a, b);
        }
        else {
            int x, y; cin >> x >> y;
            auto [a, b] = split(root, x-1);
            auto [c, d] = split(b, y-x+1);
            cout << c->sum << endl;
            b = merge(c, d);
            root = merge(a, b);
        }
    }
}
int main(){
    IO;
    solve();
}