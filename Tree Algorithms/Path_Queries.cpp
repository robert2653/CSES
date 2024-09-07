#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Info, class Tag>
struct LinkCutTree { // 1-based
    struct Node {
        Info info = Info();
        Tag tag = Tag();
        bool rev = false;
        int size = 0;
        int ch[2];
        int p = 0;
    };
    vector<Node> nd;
    void init(int n = 0) {
        nd.clear();
        nd.emplace_back();
        resize(n);
    }
    void resize(int n) {
        nd.resize(n + 1);
    }
    bool isrt(int t) {
        return !nd[t].p || (nd[nd[t].p].ch[0] != t && nd[nd[t].p].ch[1] != t);
    }
    void make_rev(int t) {
        swap(nd[t].ch[0], nd[t].ch[1]);
        nd[t].rev ^= true;
    }
    void apply(int t, const Tag &v) {
        nd[t].info.apply(nd[t].size, v);
        nd[t].tag.apply(v);
    }
    void push(int t) {
        if (nd[t].rev) {
            if (nd[t].ch[0]) make_rev(nd[t].ch[0]);
            if (nd[t].ch[1]) make_rev(nd[t].ch[1]);
            nd[t].rev = false;
        }
        if (nd[t].ch[0]) apply(nd[t].ch[0], nd[t].tag);
        if (nd[t].ch[1]) apply(nd[t].ch[1], nd[t].tag);
        nd[t].tag = Tag();
    }
    void pull(int t) {
        nd[t].size = 1 + nd[nd[t].ch[0]].size + nd[nd[t].ch[1]].size;
        nd[t].info.pull(nd[nd[t].ch[0]].info, nd[nd[t].ch[1]].info);
    }
    int pos(int t) {
        return nd[nd[t].p].ch[1] == t;
    }
    void pushAll(int t) {
        if (!isrt(t)) {
            pushAll(nd[t].p);
        }
        push(t);
    }
    void rotate(int t) {
        int q = nd[t].p;
        int x = !pos(t);
        nd[q].ch[!x] = nd[t].ch[x];
        if (nd[t].ch[x]) nd[nd[t].ch[x]].p = q;
        nd[t].p = nd[q].p;
        if (!isrt(q)) nd[nd[q].p].ch[pos(q)] = t;
        nd[t].ch[x] = q;
        nd[q].p = t;
        pull(q);
    }
    void splay(int t) {
        pushAll(t);
        while (!isrt(t)) {
            if (!isrt(nd[t].p)) {
                if (pos(t) == pos(nd[t].p)) {
                    rotate(nd[t].p);
                } else {
                    rotate(t);
                }
            }
            rotate(t);
        }
        pull(t);
    }
    void access(int t) { // access 後自動 splay
        for (int i = t, q = 0; i; q = i, i = nd[i].p) {
            splay(i);
            nd[i].ch[1] = q;
            pull(i);
        }
        splay(t);
    }
    void makeRoot(int t) {
        access(t);
        make_rev(t);
    }
    int findRoot(int t) {
        access(t);
        int x = t;
        while (nd[x].ch[0]) {
            push(x);
            x = nd[x].ch[0];
        }
        access(x);
        return x;
    }
    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
    bool neighber(int x, int y) {
        makeRoot(x);
        access(y);
        if (nd[y].ch[0] != x || nd[x].ch[1]) return false;
        return true;
    }
    void split(int rt, int y) {
        makeRoot(y);
        access(rt);
    }
    void link(int t, int p) {
        makeRoot(t);
        if (findRoot(p) != t) {
            nd[t].p = p;
        }
    }
    bool cut(int x, int y) {
        makeRoot(x);
        access(y);
        if (nd[y].ch[0] != x || nd[x].ch[1]) return false;
        nd[y].ch[0] = nd[nd[y].ch[0]].p = 0;
        pull(x);
        pull(y);
        return true;
    }
    void modify(int x, const Info &v) {
        access(x);
        nd[x].info = v;
    }
    void path_apply(int x, int y, const Tag &v) {
        assert(connected(x, y));
        split(x, y);
        apply(x, v);
    }
    Info path_query(int x, int y) {
        assert(connected(x, y));
        split(x, y);
        return nd[x].info;
    }
};
struct Tag {
    void apply(const Tag &v) {}
};
struct Info {
    ll val = 0; ll sum = 0;
    void apply(int size, const Tag &v) {}
    void pull(const Info &l, const Info &r) {
        sum = l.sum + r.sum + val;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    LinkCutTree<Info, Tag> lct;
    lct.resize(n);
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        lct.nd[i].info.val = x;
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
        lct.modify(u, lct.path_query(u, u));
        assert(lct.neighber(u, v));
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int p, x;
            cin >> p >> x;
            lct.modify(p, {x});
        } else {
            int p;
            cin >> p;
            cout << lct.path_query(1, p).sum << "\n";
        }
    }

    return 0;
}