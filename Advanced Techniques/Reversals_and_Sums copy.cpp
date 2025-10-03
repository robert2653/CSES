#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class Info, class Tag = bool()>
struct Treap {
    vector<Info> info;
    // vector<Tag> tag;
    vector<int> siz, par, rev, pri;
    vector<array<int, 2>> ch;
    Treap(int n) : info(n + 1),
        // tag(n + 1),
        siz(n + 1),
        par(n + 1), rev(n + 1), pri(n + 1), ch(n + 1) {
        for (int i = 1; i <= n; i++)
            siz[i] = 1, pri[i] = rand();
    }
    // void apply(int t, const Tag &v) {
    //     info[t].apply(siz[t], v);
    //     tag[t].apply(v);
    // }
    void push(int t) {
        if (rev[t]) {
            swap(ch[t][0], ch[t][1]);
            if (ch[t][0]) {
                rev[ch[t][0]] ^= 1;
            }
            if (ch[t][1]) {
                rev[ch[t][1]] ^= 1;
            }
            rev[t] = 0;
        }
        // apply(ch[t][0], tag[t]);
        // apply(ch[t][1], tag[t]);
        // tag[t] = Tag();
    }
    void pull(int t) {
        siz[t] = 1 + siz[ch[t][0]] + siz[ch[t][1]];
        info[t].pull(info[ch[t][0]], info[ch[t][1]]);
    }
    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        push(a), push(b);
        if (pri[a] > pri[b]) {
            ch[a][1] = merge(ch[a][1], b);
            pull(a);
            return a;
        } else {
            ch[b][0] = merge(a, ch[b][0]);
            pull(b);
            return b;
        }
    }
    pair<int, int> split(int t, int k) {
        if (!t) return {0, 0};
        push(t);
        if (siz[ch[t][0]] < k) {
            auto [a, b] = split(ch[t][1], k - siz[ch[t][0]] - 1);
            ch[t][1] = a;
            pull(t);
            return {t, b};
        } else {
            auto [a, b] = split(ch[t][0], k);
            ch[t][0] = b;
            pull(t);
            return {a, t};
        }
    }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int t, F &&pred) {
        if (!t) return 0;
        push(t);
        if (!pred(info[t])) return 0;
        if (!ch[t][0]) return 1;
        int idx = findFirst(ch[t][0], pred);
        if (!idx) idx = 1 + siz[ch[t][0]] + findFirst(ch[t][1], pred);
        return idx;
    }
    int getPos(int rt, int t) { // get t's index in array
        int res = siz[t] + 1;
        while (t != rt) {
            int p = par[t];
            if (ch[p][1] == t) {
                res += siz[ch[p][0]] + 1;
            }
            t = p;
        }
        return res;
    }
    void getArray(int t, vector<Info> &a) {
        if (!t) return;
        push(t);
        getArray(ch[t][0], a);
        a.push_back(info[t]);
        getArray(ch[t][1], a);
    }
};

struct Info {
    int v = 0;
    ll sum = 0;
    void pull(const Info &l, const Info &r) {
        sum = v + l.sum + r.sum;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, q;
    cin >> n >> q;
    Treap<Info> t(n);
    int rt = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        t.info[i + 1].v = x;
        t.info[i + 1].sum = x;
        rt = t.merge(rt, i + 1);
    }
    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;  // 1 for rev, 2 for query
        if (op == 1) {
            int x, y;
            cin >> x >> y;
            if (x == y) {
                continue;
            }
            auto [a, b] = t.split(rt, x - 1);
            auto [c, d] = t.split(b, y - x + 1);
            t.rev[c] ^= true;
            b = t.merge(c, d);
            rt = t.merge(a, b);
        } else {
            int x, y;
            cin >> x >> y;
            auto [a, b] = t.split(rt, x - 1);
            auto [c, d] = t.split(b, y - x + 1);
            cout << t.info[c].sum << "\n";
            b = t.merge(c, d);
            rt = t.merge(a, b);
        }
    }
    return 0;
}