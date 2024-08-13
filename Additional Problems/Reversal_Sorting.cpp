#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Treap {
    Treap *lc, *rc;
    int pri, siz; bool rev_valid;
    int val; int min;
    Treap(int val_) {
        min = val = val_;
        pri = rand();
        lc = rc = nullptr;
        siz = 1; rev_valid = 0;
    }
    void pull() { // update siz or other information
        siz = 1;
        min = val;
        for (auto c : {lc, rc}) {
            if (!c) continue;
            siz += c->siz;
            min = std::min(min, c->min);
        }
    }
    void push() {
        if (rev_valid) {
            swap(lc, rc);
            if (lc) lc->rev_valid ^= 1;
            if (rc) rc->rev_valid ^= 1;
        }
        rev_valid = false;
    }
    int find(int k) { // 找到 min 是 k 的位置 (1-based)
        push();
        int ls = (lc ? lc->siz : 0) + 1;
        if (val == k) return ls;
        if (lc && lc->min == k) return lc->find(k);
        else return rc->find(k) + ls;
    }
};
int size(Treap *t) {
    return t ? t->siz : 0;
}
Treap *merge(Treap *a, Treap *b) {
    if (!a || !b) return a ? a : b;
    a->push(); b->push();
    if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        a->pull();
        return a;
    }
    else {
        b->lc = merge(a, b->lc);
        b->pull();
        return b;
    }
}
pair<Treap*, Treap*> split(Treap *t, int k) {
    // 分割前 k 個在 first，剩下的在 second
	if (t == nullptr) return {nullptr, nullptr};
    t->push();
	if (size(t->lc) < k) {
		auto [a, b] = split(t->rc, k - size(t->lc) - 1);
		t->rc = a;
		t->pull();
		return {t, b};
	}
    else {
		auto [a, b] = split(t->lc, k);
		t->lc = b;
		t->pull();
		return {a, t};
	}
}
void Print(Treap *t) {
    if (!t) return;
    t->push();
    Print(t->lc);
    cout << t->val;
    Print(t->rc);
}

void solve() {
    int n; cin >> n;
    Treap *t = nullptr;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        t = merge(t, new Treap(x));
    }
    vector<pair<int, int>> ans;
    for (int i = 0; i < n; i++) {
        int pos = t->find(i + 1);
        Treap *l, *m, *r;

        auto res = split(t, pos);
        m = res.first; r = res.second;

        res = split(m, pos - 1);
        l = res.first;
        // m 是那個 i 點，直接捨棄掉

        if (l) l->rev_valid ^= 1;
        t = merge(l, r);
        ans.emplace_back(i + 1, pos + i);
    }
    cout << ans.size() << "\n";
    for (auto [i, j] : ans) cout << i << " " << j << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}