#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class Info>
struct Treap {
    Treap *lc, *rc, *par;
    int pri, siz;
    bool rev_valid;
    Info info;
    Treap(Info info) : info(info) {
        pri = rand();
        lc = rc = par = nullptr;
        siz = 1, rev_valid = false;
    }
    void pull() {
        siz = 1;
        Info param[2] {Info(), Info()};
        if (lc) siz += lc->siz, lc->par = this, param[0] = lc->info;
        if (rc) siz += rc->siz, rc->par = this, param[0] = rc->info;
        info.pull(param[0], param[1]);
    }
    void push() {
        if (rev_valid) {
            swap(lc, rc);
            if (lc) lc->rev_valid ^= 1;
            if (rc) rc->rev_valid ^= 1;
        }
        rev_valid = false;
    }
};
template<class Info>
int size(Treap<Info> *t) { return t ? t->siz : 0; }

template<class Info>
Treap<Info> *merge(Treap<Info> *a, Treap<Info> *b) {
    if (!a || !b) return a ? a : b;
    a->push(); b->push();
    if (a->pri > b->pri) {
        a->rc = merge(a->rc, b);
        a->pull();
        return a;
    } else {
        b->lc = merge(a, b->lc);
        b->pull();
        return b;
    }
}

template<class Info>
pair<Treap<Info>*, Treap<Info>*> split(Treap<Info> *t, int k) {
    // 分割前 k 個在 first，剩下的在 second
    if (t == nullptr) return {nullptr, nullptr};
    t->push();
    if (size(t->lc) < k) {
        auto [a, b] = split(t->rc, k - size(t->lc) - 1);
        t->rc = a;
        if (a) a->par = t;
        if (b) b->par = nullptr;
        t->pull();
        return {t, b};
    } else {
        auto [a, b] = split(t->lc, k);
        t->lc = b;
        if (b) b->par = t;
        if (a) a->par = nullptr;
        t->pull();
        return {a, t};
    }
}

template<class Info>
void printArray(Treap<Info> *t) {
    if (!t) return;
    t->push();
    printArray(t->lc);
    cout << t->info;
    printArray(t->rc);
}

template<class Info, class F>
int findFirst(Treap<Info> *t, F &&pred) { // 1-based
    if (!pred(t->info)) return 0;
    t->push();
    if (!t->lc && !t->rc) return 1;
    int ls = t->lc ? t->lc->siz : 0;
    if (t->lc && pred(t->info)) return findFirst(t->lc, pred) + 1;
    else return findFirst(t->rc, pred) + ls + 1;
}

template<class Info>
int getpos(Treap<Info> *rt, Treap<Info> *t) {
    int pos = (t->lc ? t->lc->siz : 0) + 1;
    while (t != rt) {
        Treap *par = nd->par;
        if (par->rc == t) {
            pos += (par->lc ? par->lc->siz : 0) + 1;
        }
        t = par;
    }
    return pos;
}

struct Info {
    int v = 0;
    ll sum = 0;
    void pull(const Info &l, const Info &r) {
        sum = v + l.sum + r.sum;
        // min = std::min(min, ch.min);
    }
    friend ostream &operator<<(ostream &os, const Info &info) {
        os << info.v << " ";
        return os;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Treap<Info> *root = nullptr;
    for (int i = 0; i < n; i++) {
        int tmp;
        cin >> tmp;
        root = merge(root, new Treap<Info>({tmp, tmp}));
    }
    for (int i = 0; i < m; i++) {
        int op;
        cin >> op;  // 1 for rev, 2 for query
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (x == y) {
                continue;
            }
            auto [a, b] = split(root, x - 1);
            auto [c, d] = split(b, y - x + 1);
            c->rev_valid ^= true;
            b = merge(c, d);
            root = merge(a, b);
        } else {
            int x, y;
            cin >> x >> y;
            auto [a, b] = split(root, x - 1);
            auto [c, d] = split(b, y - x + 1);
            cout << c->info.sum << "\n";
            b = merge(c, d);
            root = merge(a, b);
        }
    }
    return 0;
}