#include <bits/stdc++.h>
 
using namespace std;
using ll = long long;
 
template<class Info, class Tag = bool()>
struct SegmentTree { // [l, r), uncomment /**/ to lazy
    int n;
    vector<Info> info;
    /*
    vector<Tag> tag;
    */
    template<class T>
    SegmentTree(const vector<T> &init) {
        n = init.size();
        info.assign(4 << __lg(n), Info());
        /*
        tag.assign(4 << __lg(n), Tag());
        */
        function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init[l];
                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    /*
    void apply(int p, int l, int r, const Tag &v) {
        info[p].apply(l, r, v);
        tag[p].apply(v);
    }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        if (r - l >= 1) {
            apply(2 * p, l, m, tag[p]);
            apply(2 * p + 1, m, r, tag[p]);
        }
        tag[p] = Tag();
    }
    */
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        /*
        push(p, l, r);
        */
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
        /*
        push(p, l, r);
        */
        return query(2 * p, l, m, ql, qr) + query(2 * p + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }
    /*
    void rangeApply(int p, int l, int r, int ql, int qr, const Tag &v) {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        rangeApply(2 * p, l, m, ql, qr, v);
        rangeApply(2 * p + 1, m, r, ql, qr, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        rangeApply(1, 0, n, l, r, v);
    }
    */
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) return -1;
        if (l >= x && r <= y && !pred(info[p])) return -1;
        if (r - l == 1) return l;
        int m = (l + r) / 2;
        /*
        push(p, l, r);
        */
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1)
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
struct Info_Prv {
    int mx = -1;
    Info_Prv &operator=(const int &rhs) & {
        mx = rhs;
        return *this;
    }
};
Info_Prv operator+(const Info_Prv &a, const Info_Prv &b) {
    return { max(a.mx, b.mx) };
}

void solve_prv() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> sorted;
    vector<array<int, 3>> qry;
    vector<int> prv(n, -1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sorted.push_back(a[i]);
    }
    for (int i = 0; i < q; i++) {
        int op, p, x;
        cin >> op >> p >> x;
        if (op == 1) {
            sorted.push_back(x);
        }
        qry.push_back({op, p, x});
    }
    sort(sorted.begin(), sorted.end());
    sorted.resize(unique(sorted.begin(), sorted.end()) - sorted.begin());
    int m = sorted.size();
    vector<set<int>> rec(m);
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(sorted.begin(), sorted.end(), a[i]) - sorted.begin();
        if (!rec[a[i]].empty()) {
            prv[i] = *rec[a[i]].rbegin();
        }
        rec[a[i]].insert(i);
    }
    SegmentTree<Info_Prv> seg(prv);
    for (int i = 0; i < q; i++) {
        int op = qry[i][0];
        cin >> op;
        if (op == 1) {
            int p = qry[i][1] - 1;
            int x = qry[i][2];
            x = lower_bound(sorted.begin(), sorted.end(), x) - sorted.begin();
            // delete
            auto now = rec[a[p]].lower_bound(p);
            auto nxt = rec[a[p]].upper_bound(p);
            if (nxt != rec[a[p]].end()) { // 更新 nxt 的 prv
                if (now == rec[a[p]].begin()) { // 沒有前一個
                    prv[*nxt] = -1;
                } else {
                    prv[*nxt] = *prev(now);
                }
                seg.modify(*nxt, {prv[*nxt]});
            }
            rec[a[p]].erase(p);
            // insert
            a[p] = x;
            rec[a[p]].insert(p);
            now = rec[a[p]].lower_bound(p);
            nxt = rec[a[p]].upper_bound(p);
            if (now != rec[a[p]].begin()) { // 不是第一個
                prv[p] = *prev(now);
            } else {
                prv[p] = -1;
            }
            seg.modify(p, {prv[p]});    // 更新 p 的 prv
            if (nxt != rec[a[p]].end()) {   // 更新 nxt 的 prv 為 p
                prv[*nxt] = p;
                seg.modify(*nxt, {p});
            }
        } else {
            int l = qry[i][1] - 1;
            int r = qry[i][2];
            cout << (seg.query(l, r).mx >= l ? "NO\n" : "YES\n");
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    solve_prv();
    return 0;
}