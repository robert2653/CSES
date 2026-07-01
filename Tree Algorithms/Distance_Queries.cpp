#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Info {
    int siz = 0; // 實鏈的長度
    void pull(const Info &l, const Info &r) {
        siz = 1 + l.siz + r.siz;
    }
};
struct LinkCutTree { // 1-based
    vector<Info> info;
    vector<array<int, 2>> ch;
    vector<int> p, rev;
    LinkCutTree(int n) : info(n + 1), ch(n + 1), p(n + 1), rev(n + 1) {}
    bool isrt(int x) {
        return ch[p[x]][0] != x && ch[p[x]][1] != x;
    }
    int pos(int x) { // x 是其 par 的左/右
        return ch[p[x]][1] == x;
    }
    void applyRev(int x) {
        if (!x) return;
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
    }
    void push(int x) {
        if (rev[x]) {
            applyRev(ch[x][0]);
            applyRev(ch[x][1]);
            rev[x] = 0;
        }
    }
    void pull(int x) {
        if (!x) return;
        info[x].pull(info[ch[x][0]], info[ch[x][1]]);
    }
    void pushAll(int x) {
        if (!isrt(x)) pushAll(p[x]);
        push(x);
    }
    void rotate(int x) { // x 與其 par 交換位置
        int f = p[x], r = pos(x);
        ch[f][r] = ch[x][!r];
        if (ch[x][!r]) p[ch[x][!r]] = f;
        p[x] = p[f];
        if (!isrt(f)) ch[p[f]][pos(f)] = x;
        ch[x][!r] = f, p[f] = x;
        pull(f), pull(x);
    }
    void splay(int x) { // x 旋轉到當前的根
        pushAll(x);
        for (int f = p[x]; f = p[x], !isrt(x); rotate(x))
            if (!isrt(f)) rotate(pos(x) == pos(f) ? f : x);
    }
    // access(x), access(y) 可以回傳 LCA
    int access(int x) { // 根到 x 換成實鏈
        int c;
        for (c = 0; x; c = x, x = p[x]) {
            splay(x);
            ch[x][1] = c;
            pull(x);
        }
        return c;
    }
    void makeRoot(int x) { // x 變成所在樹的根
        access(x), splay(x), applyRev(x);
    }
    int findRoot(int x) {
        access(x), splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x); return x;
    }
    void split(int rt, int x) { // 以 rt 為根, x 為子樹根
        makeRoot(x), access(rt), splay(rt);
    }
    void link(int rt, int x) { // 以 rt 為根, x 為子樹根
        makeRoot(rt);
        access(x), splay(x);
        p[rt] = x;
        pull(x);
    }
    void cut(int rt, int x) { // 以 rt 為根, x 為子樹根
        split(rt, x);
        ch[rt][0] = p[x] = 0;
        pull(rt);
    }
    bool connected(int x, int y) {
        return findRoot(x) == findRoot(y);
    }
    bool neighbor(int x, int y) {
        if (!connected(x, y)) return false;
        split(x, y);
        return info[x].siz == 2; // psiz
    }
    void modify(int x, const Info &i) {
        access(x), splay(x);
        info[x] = i, pull(x);
    }
    Info pathQuery(int x, int y) {
        assert(connected(x, y));
        split(x, y); return info[x];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;

    LinkCutTree lct(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        lct.link(a, b);
    }
    while (q--) {
        int a, b;
        cin >> a >> b;
        cout << lct.pathQuery(a, b).siz - 1 << "\n";
    }
    return 0;
}