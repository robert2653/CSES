#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
constexpr int inf = 1e9;
 
struct Info {
    int val = 0;
    int max = 0;
};
 
struct Node {
    Node *ch[2], *p;
    int rev = 0;
    int size = 1;
    void make_rev() {
        swap(ch[0], ch[1]);
        rev ^= 1;
    }
    Node() : ch {nullptr, nullptr}, p(nullptr) {}
 
    Info info = Info();
 
    void push_tag() {
        if (rev) {
            if (ch[0]) ch[0]->make_rev();
            if (ch[1]) ch[1]->make_rev();
            rev = 0;
        }
    }
    void pull_info() {
        size = (ch[0] ? ch[0]->size : 0) + (ch[1] ? ch[1]->size : 0) + 1;
        info.max = info.val;
        if (ch[0]) {
            info.max = max(info.max, ch[0]->info.max);
        }
        if (ch[1]) {
            info.max = max(info.max, ch[1]->info.max);
        }
    }
};
 
bool isroot(Node *t) {
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) { // 回傳 1 代表是右子節點
    return t->p->ch[1] == t;
}
void pushAll(Node *t) {
    if (!isroot(t)) {
        pushAll(t->p);
    }
    t->push_tag();
}
void rotate(Node *t) {
    Node *q = t->p;
    int x = !pos(t);
    q->ch[!x] = t->ch[x];
    if (t->ch[x]) {
        t->ch[x]->p = q;
    }
    t->p = q->p;
    if (!isroot(q)) {
        q->p->ch[pos(q)] = t;
    }
    t->ch[x] = q;
    q->p = t;
    q->pull_info();
}
void splay(Node *t) { // 單點修改前必須呼叫
    // 把 t 旋轉到目前 splay 的根
    pushAll(t);
    while (!isroot(t)) {
        Node* p = t->p;
        if (!isroot(p)) {
            if (pos(t) == pos(p)) {
                rotate(p);
            } else {
                rotate(t);
            }
        }
        rotate(t);
    }
    t->pull_info();
}
void access(Node *t) {  // 初始化都先 access
    // 把從根到 t 的所有點都放在一條實鏈裡，使根
    // 到 t 成為一條實路徑，並且在同一棵 splay 裡
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        i->ch[1] = q;
        i->push_tag();
        i->pull_info();
    }
    splay(t);
}
void makeRoot(Node *t) { // 使 t 點成為其所在樹的根
    access(t);
    swap(t->ch[0], t->ch[1]);
    t->rev ^= 1;
}
Node* findRoot(Node *t) { // 找到 t 的 root
    access(t);
    splay(t);
    t->push_tag();
    while (t->ch[0]) {
        t = t->ch[0];
        t->push_tag();
    }
    splay(t);
    return t;
}
void link(Node *t, Node *p) {
    makeRoot(t);
    if (findRoot(p) != t) {
        makeRoot(p);
        t->p = p;
        p->pull_info();
    }
}
bool cut(Node *x, Node *y) { // 不存在邊，回傳 false
	makeRoot(x);
    access(y);
    if (y->ch[0] != x || x->ch[1]) return false;
    y->ch[0]->p = nullptr;
    y->ch[0] = nullptr;
    y->pull_info();
    return true;
}
void split(Node *x, Node *y) { // 以 y 做根, 區間修改用, apply 在 y 上
    makeRoot(x);
    access(y);
    splay(y);
}
 
bool isconnected(Node *x, Node *y) { // 查詢有沒有連通
	makeRoot(x);
    access(y);
    return findRoot(x) == findRoot(y);
}
 
void solve() {
    int n, m, q;
    cin >> n >> m >> q;
    vector<Node *> nodes(n + m);
 
    for (int i = 0; i < n + m; i++) {
        nodes[i] = new Node();
    }
 
    for (int i = 0; i < m; i++) {
        int u, v; 
        cin >> u >> v;
        u--; v--;
        nodes[n + i]->info.val = nodes[n + i]->info.max = i + 1;
        if(!isconnected(nodes[u], nodes[v])) {
            link(nodes[u], nodes[n + i]);
            link(nodes[v], nodes[n + i]);
        }
    }
 
    for (int i = 0; i < q; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        if (!isconnected(nodes[u], nodes[v])) {
            cout << -1 << "\n";
        } else {
            split(nodes[u], nodes[v]);
            cout << nodes[v]->info.max << "\n";
        }
    }
}
 
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}