#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

struct Node {
    int add, mul;
    int val, sum, size;
    Node *ch[2], *p;
    Node() : ch {nullptr, nullptr}, p(nullptr) {}
    
    void update() { // 更新節點的值

    }
};
void push(Node *t) { // 在 Access 操作之後，遞歸地從上到下 PushDown 更新資訊
    
}
void pull(Node *t) {

}
bool isroot(Node *t) { // 判斷 x 是否是所在樹的根。
    return t->p == nullptr || (t->p->ch[0] != t && t->p->ch[1] != t);
}
int pos(Node *t) {
    return t->p->ch[1] == t;
}
void pushAll(Node *t) {
    if (!isroot(t)) {
        pushAll(t->p);
    }
    push(t);
}
void rotate(Node *t) { // 將 x 向上旋轉一層的操作
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
    pull(q);
}
void splay(Node *t) { // 透過和 Rotate 操作連動實現把 x 旋轉到目前 Splay 的根
    pushAll(t);
    while (!isroot(t)) {
        if (!isroot(t->p)) {
            if (pos(t) == pos(t->p)) {
                rotate(t->p);
            } else {
                rotate(t);
            }
        }
        rotate(t);
    }
    pull(t);
}
 
void access(Node *t) {
    // 把從根到 x 的所有點都放在一條實鏈裡，使根到 x 成為一條實路徑
    // 並且在同一棵 Splay 裡。只有此操作是必須實現的，其他操作視題目而實現。
    for (Node *i = t, *q = nullptr; i; q = i, i = i->p) {
        splay(i);
        i->ch[1] = q;
        i->update();
        pull(i);
    }
    splay(t);
}