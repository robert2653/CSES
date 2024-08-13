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
    int pri, subsize; char val;
    Treap(int _val){
        val = _val;
        pri = rand();
        l = r = nullptr;
        subsize = 1;
    }
    void pull(){
        subsize = 1;
        for(auto i: {l,r})
            if(i) subsize += i->subsize;
    }
};
int size(Treap *treap) {
    if (treap == NULL) return 0;
    return treap->subsize;
}
Treap *merge(Treap *a, Treap *b){
    if(!a || !b) return a ? a : b;
    if(a->pri > b->pri){
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
void Print(Treap *t){
    if(t){
        Print(t->l);
        cout << t->val;
        Print(t->r);
    }
}
void solve(){
    int n, m; cin >> n >> m;
    Treap *root = nullptr;
    string str; cin >> str;
    for(auto c : str){
        root = merge(root, new Treap(c));
    }
    rep(i, 1, m){
        int x, y; cin >> x >> y;
        auto [a, b] = split(root, x-1);
        auto [c, d] = split(b, y-x+1);
        b = merge(a, d);    // 1、3先河，2(中間)最後和放在最右邊
        root = merge(b, c);
    }
    Print(root);
}
int main(){
    IO;
    solve();
}