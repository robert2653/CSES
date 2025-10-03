#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const ll inf = -1E18;
struct Line {
    ll m, b;
    Line(ll m = 0, ll b = inf) : m(m), b(b) {}
    ll eval(ll x) { return m * x + b; }
};
struct LiChaoSeg {
    struct Node {
        Line line;
        int l = -1, r = -1;
    };
    ll n; vector<Node> nd;
    LiChaoSeg(ll n) : n(n) { newNode(); }
    void addLine(Line line) { update(0, 0, n, line); }
    void rangeAddLine(Line line, ll ql, ll qr) { rangeUpdate(0, 0, n, ql, qr, line); }
    ll query(ll x) { return query(x, 0, 0, n); }
private:
    int newNode() {
        nd.emplace_back();
        return nd.size() - 1;
    }
    void update(int p, ll l, ll r, Line line) {
        ll m = (l + r) / 2;
        bool left = line.eval(l) > nd[p].line.eval(l);
        bool mid = line.eval(m) > nd[p].line.eval(m);
        if (mid) swap(nd[p].line, line);
        if (r - l == 1) return;
        if (left != mid) {
            if (nd[p].l == -1) nd[p].l = newNode();
            update(nd[p].l, l, m, line);
        } else {
            if (nd[p].r == -1) nd[p].r = newNode();
            update(nd[p].r, m, r, line);
        }
    }
    void rangeUpdate(int p, ll l, ll r, ll ql, ll qr, Line line) {
        if (r <= ql || l >= qr) return;
        if (ql <= l && r <= qr) return update(p, l, r, line);
        ll m = (l + r) / 2;
        if (nd[p].l == -1) nd[p].l = newNode();
        if (nd[p].r == -1) nd[p].r = newNode();
        rangeUpdate(nd[p].l, l, m, ql, qr, line);
        rangeUpdate(nd[p].r, m, r, ql, qr, line);
    }
    ll query(ll x, int p, ll l, ll r) {
        if (p == -1) return inf;
        ll m = (l + r) / 2;
        if (x < m) return max(nd[p].line.eval(x), query(x, nd[p].l, l, m));
        else return max(nd[p].line.eval(x), query(x, nd[p].r, m, r));
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    LiChaoSeg seg(100005);
    while (n--) {
        int op;
        cin >> op;
        if (op == 1) {
            int a, b;
            cin >> a >> b;
            seg.addLine(Line(a, b));
        } else {
            int x;
            cin >> x;
            cout << seg.query(x) << "\n";
        }
    }
    return 0;
}