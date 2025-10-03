#include <bits/stdc++.h>
using namespace std;

template<class Info>
struct Treap {
    vector<Info> info;
    vector<int> siz, par, rev, pri;
    vector<array<int, 2>> ch;
    Treap(int n) : info(n + 1), siz(n + 1), par(n + 1),
    rev(n + 1), pri(n + 1), ch(n + 1) {
        for (int i = 1; i <= n; i++)
            siz[i] = 1, pri[i] = rand();
    }
    void push(int t) {
        if (rev[t]) {
            swap(ch[t][0], ch[t][1]);
            if (ch[t][0]) rev[ch[t][0]] ^= 1;
            if (ch[t][1]) rev[ch[t][1]] ^= 1;
            rev[t] = 0;
        }
    }
    void pull(int t) {
        siz[t] = 1 + siz[ch[t][0]] + siz[ch[t][1]];
    }
    int merge(int a, int b) {
        if (!a || !b) return a ? a : b;
        push(a), push(b);
        if (pri[a] > pri[b]) {
            ch[a][1] = merge(ch[a][1], b);
            pull(a); return a;
        } else {
            ch[b][0] = merge(a, ch[b][0]);
            pull(b); return b;
        }
    }
    pair<int, int> split(int t, int k) {
        if (!t) return {0, 0};
        push(t);
        if (siz[ch[t][0]] >= k) {
            auto [a, b] = split(ch[t][0], k);
            ch[t][0] = b, pull(t);
            return {a, t};
        } else {
            auto [a, b] = split(ch[t][1], k - siz[ch[t][0]] - 1);
            ch[t][1] = a, pull(t);
            return {t, b};
        }
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
    char c;
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    string s;
    cin >> s;

    Treap<Info> tr(n);
    int rt = 0;
    for (int i = 0; i < n; i++) {
        tr.info[i + 1].c = s[i];
        rt = tr.merge(rt, i + 1);
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        int l, m, r;
        tie(l, r) = tr.split(rt, x - 1);
        tie(m, r) = tr.split(r, y - x + 1);
        rt = tr.merge(tr.merge(l, r), m);
    }
    vector<Info> ans;
    tr.getArray(rt, ans);
    for (int i = 0; i < n; i++) {
        cout << ans[i].c;
    }

    return 0;
}