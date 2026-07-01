#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

struct Info {
    int siz = 0, vsiz = 0, psiz = 0;
    ll sumL = 0, sumR = 0, vsum = 0; 
    
    void pull(const Info &l, const Info &r) {
        psiz = 1 + l.psiz + r.psiz;
        siz = 1 + l.siz + r.siz + vsiz;
        
        // 左子樹代表在實鏈上方的節點，右子樹代表在實鏈下方的節點
        sumL = l.sumL 
             + vsum + 1LL * (vsiz + 1) * l.psiz 
             + r.sumL + 1LL * r.siz * (l.psiz + 1);
             
        sumR = r.sumR 
             + vsum + 1LL * (vsiz + 1) * r.psiz 
             + l.sumR + 1LL * l.siz * (r.psiz + 1);
    }
    void operator+=(const Info &i) { 
        vsiz += i.siz;
        // 虛邊連接的是子樹實鏈的頂端，距離多 1 步
        vsum += i.sumL + i.siz; 
    }
    void operator-=(const Info &i) { 
        vsiz -= i.siz;
        vsum -= i.sumL + i.siz;
    }
    void reverse() {
        swap(sumL, sumR);
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
        info[x].reverse();
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
        info[x] = i, pull(x);
    }
    Info pathQuery(int x, int y) {
        assert(connected(x, y));
        split(x, y); return info[x];
    }
    // Info subtreeQuery(int rt, int x) { // 以 rt 當 root, x 的 subtree
    //     assert(connected(rt, x));
    //     makeRoot(rt);
    //     access(x), splay(x);
    //     return info[x].asSubtree();
    // }
    Info componentQuery(int x) {
        makeRoot(x);
        return info[x];
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    LinkCutTree lct(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        lct.link(u, v);
    }
    for (int i = 1; i <= n; i++) {
        lct.makeRoot(i);
        cout << lct.info[i].sumL << " \n"[i == n];
    }
    
    return 0;
}