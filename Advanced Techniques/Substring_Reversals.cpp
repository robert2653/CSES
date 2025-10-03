#include <bits/stdc++.h>
using namespace std;

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
        for (auto c : {lc, rc}) {
            if (!c) continue;
            siz += c->siz;
            c->par = this;
            info.pull(c->info);
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
        t->pull();
        if (b) b->par = nullptr;
        return {t, b};
    } else {
        auto [a, b] = split(t->lc, k);
        t->lc = b;
        t->pull();
        if (a) a->par = nullptr;
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

struct Info {
    char c;
    void pull(const Info &ch) {
        // min = std::min(min, ch.min);
    }
    friend ostream &operator<<(ostream &os, const Info &info) {
        os << info.c << "";
        return os;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    Treap<Info> *root = nullptr;
    string str; cin >> str;
    for(auto c : str){
        root = merge(root, new Treap<Info>({c}));
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        auto [a, b] = split(root, x - 1);
        auto [c, d] = split(b, y - x + 1);
        c->rev_valid ^= true;
        b = merge(c, d);
        root = merge(a, b);
    }
    printArray(root);
    return 0;
}