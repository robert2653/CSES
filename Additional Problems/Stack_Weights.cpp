// 首先先講一個結論：
// 定義 $sufl_i$ 為放置在左邊且編號 $\geq i$ 的數量，$sufr_i$ 為放置在右邊且編號 $\geq i$ 的數量
// 則若左邊的重量確定小於右邊須滿足：
// $\forall i, sufl_i \leq sufr_i$
// 若是我們計算出 $c_i = sufl_i - sufr_i$，則

// $\forall i, c_i \leq 0$，則代表右邊較重
// $\forall i, c_i \geq 0$，則代表左邊較重
// 無法分辨

// 所以就開一棵存取最大值和最小值的線段樹，放入一個硬幣就相當於對一個前綴 +1 或是 -1
// 之後就可以用全域的最大值和最小值判斷大小關係

#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <class Info, class Tag>
struct LazySeg {    // 左閉右開寫法
    int n;
    vector<Info> info;
    vector<Tag> tag;
    LazySeg() : n(0) {}
    LazySeg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template <class T>
    LazySeg(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init (vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        tag.assign(4 << __lg(n), Tag());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }
    void apply(int p, int l, int r, const Tag &v) {
        info[p].apply(l, r, v);
        tag[p].apply(v);
    }
    void push(int p, int l, int r) {
        int m = (l + r) / 2;
        if (r - l >= 1) {
            apply(p * 2, l, m, tag[p]);
            apply(p * 2 + 1, m, r, tag[p]);
        }
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
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
        push(p, l, r);
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
    void range_apply(int p, int l, int r, int ql, int qr, const Tag &v) {
        if (qr <= l || ql >= r) return;
        if (ql <= l && r <= qr) {
            apply(p, l, r, v);
            return;
        }
        int m = (l + r) / 2;
        push(p, l, r);
        range_apply(p * 2, l, m, ql, qr, v);
        range_apply(p * 2 + 1, m, r, ql, qr, v);
        pull(p);
    }
    void range_apply(int l, int r, const Tag &v) {
        range_apply(1, 0, n, l, r, v);
    }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        push(p);
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
// ---define structure and info plus---
struct Tag { // 有些 Tag 不用 push 例如 sweepLine
    int add;
    Tag(int add_ = 0) {
        add = add_;
    }
    void apply(const Tag& v) {
        add += v.add;
    }
};
struct Info {
    int min;
    int max;
    Info(int min_ = 1e9, int max_ = -1e9) {
        min = min_;
        max = max_;
    }
    void apply(int l, int r, const Tag &v) {
        min += v.add;
        max += v.add;
    }
    // Info& operator=(const Info &rhs) {
    //     // 部分 assignment 使用
    //     return *this;
    // }
};
Info operator+(const Info &a, const Info &b) {
    return { min(a.min, b.min), max(a.max, b.max) };
}

void solve() {
    int n; cin >> n;
    LazySeg<Info, Tag> lsg(vector<Info>(n, Info(0, 0)));
    for (int i = 0; i < n; i++) {
        int c, st;
        cin >> c >> st;
        lsg.range_apply(0, c, Tag(st == 1 ? 1 : -1));
        Info res = lsg.query(0, n);
        if (res.max <= 0) cout << "<\n";
        else if (res.min >= 0) cout << ">\n";
        else cout << "?\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}