#include <bits/stdc++.h>
#pragma GCC optimize("03")
using namespace std;
using ll = long long;

template<class T>
constexpr T power(T a, ll b) {
    T res {1};
    for (; b; b /= 2, a *= a)
        if (b % 2) res *= a;
    return res;
}
constexpr ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
template<ll P>
struct MInt {
    ll x;
    constexpr MInt() : x {0} {}
    constexpr MInt(ll x) : x {norm(x % getMod())} {}
    static z Mod;
    constexpr static ll getMod() {
        if (P > 0) return P;
        else return Mod;
    }
    constexpr static void setMod(ll Mod_) {
        Mod = Mod_;
    }
    constexpr ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    constexpr ll val() const { return x; }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        if (getMod() < (1ULL << 31)) {
            x = x * rhs.x % int(getMod());
        } else {
            x = mul(x, rhs.x, getMod());
        }
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs; return res *= rhs;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs; return res += rhs;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs; return res -= rhs;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs; return res /= rhs;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        ll v; is >> v; a = MInt(v); return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.val() < rhs.val();
    }
};
template<>
ll MInt<0>::Mod = 998244353;
constexpr int P = 1e9 + 7;
using Z = MInt<P>;

template <class Info>
struct Seg {    // 左閉右開寫法
    int n; vector<Info> info;
    Seg() : n(0) {}
    Seg(int n_, Info v_ = Info()) { init(n_, v_); }
    template <class T>
    Seg(vector<T> init_) { init(init_); }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
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
    void pull(int p) {
        info[p] = info[p * 2] + info[p * 2 + 1];
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v; return;
        }
        int m = (l + r) / 2;
        if (x < m) modify(2 * p, l, m, x, v);
        else modify(2 * p + 1, m, r, x, v);
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) {
        return query(1, 0, n, ql, qr);
    }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x)
            return -1;
        if (l >= x && r <= y && !pred(info[p]))
            return -1;
        if (r - l == 1)
            return l;
        int m = (l + r) / 2;
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

constexpr int B = 59;
// ---define structure and info plus---
struct Info {
    int n = 0;
    Z pref, suff;
};
Info operator+(const Info &a, const Info &b) {
    Info x;
    x.n = a.n + b.n;
    x.pref = a.pref * power(Z(B), b.n) + b.pref;
    x.suff = b.suff * power(Z(B), a.n) + a.suff;
    return x;
}

void solve() {
    int n, q;
    cin >> n >> q;
    string s;
    cin >> s;
    vector<Info> init(n);
    for (int i = 0; i < n; i++) {
        init[i].n = 1;
        init[i].pref = init[i].suff = s[i] - 'a' + 1;
    }
    Seg<Info> seg(init);

    for (int i = 0; i < q; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            int p;
            cin >> p;
            char c;
            cin >> c;
            s[p - 1] = c;
            Info x;
            x.n = 1;
            x.pref = x.suff = c - 'a' + 1;
            seg.modify(p - 1, x);
        } else {
            int a, b;
            cin >> a >> b;
            auto res = seg.query(a - 1, b);
            if (res.pref == res.suff) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
        }
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