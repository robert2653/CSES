#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
// 有用到 pathApply 才需要 apply 有關的
struct Info {
    int siz = 0, vsiz = 0, psiz = 0; // 真實子樹大小, 虛子樹大小, 實鏈長度
    ll val = 0, sum = 0, vsum = 0, psum = 0;
    void pull(const Info &l, const Info &r) {
        psiz = 1 + l.psiz + r.psiz;
        siz = 1 + l.siz + r.siz + vsiz;
        psum = (l.psum + r.psum + val);
        sum = (l.sum + r.sum + val + vsum);
    }
    void modify(const Info &i) { // 才不會蓋掉 vsum, vsiz
        val = i.val;
    }
    void operator+=(const Info &v) { // 將實邊轉虛邊時加上資訊
        vsiz += v.siz;
        vsum = (vsum + v.sum);
    }
    void operator-=(const Info &v) { // 將虛邊轉實邊時扣除資訊
        vsiz -= v.siz;
        vsum = (vsum - v.sum);
    }
    Info asSubtree() const { // 當前節點作為 Virtual Subtree 根時的狀態
        Info res;
        res.siz = vsiz + 1;
        res.sum = (vsum + val);
        return res;
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
            if (ch[x][1]) info[x] += info[ch[x][1]]; // 原右子樹轉虛邊
            if (c) info[x] -= info[c];               // 虛邊轉新右子樹
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
        info[x] += info[rt]; // rt 成為 x 的虛子樹
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
        info[x].modify(i);
        pull(x);
    }
    Info pathQuery(int x, int y) {
        assert(connected(x, y));
        split(x, y); return info[x];
    }
    Info subtreeQuery(int rt, int x) { // 以 rt 當 root, x 的 subtree
        assert(connected(rt, x));
        makeRoot(rt);
        access(x), splay(x);
        return info[x].asSubtree();
    }
    Info componentQuery(int x) {
        makeRoot(x);
        return info[x];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
 
    vector<int> a(n + 1);
    LinkCutTree lct(n);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        lct.modify(i, {.val = a[i]});
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    while (q--) {
        int op;
        cin >> op;
        if (op == 1) {
            int x, v;
            cin >> x >> v;
            a[x] = v;
            lct.modify(x, {.val = v});
        } else {
            int x;
            cin >> x;
            cout << lct.subtreeQuery(1, x).sum << "\n";
        }
    }
    return 0;
}