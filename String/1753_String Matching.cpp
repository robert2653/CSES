#include <bits/stdc++.h>

using i64 = long long;
constexpr i64 MOD = 1000000007;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}

template<i64 P>
struct MInt {
    i64 x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % MOD)} {}
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += MOD;
        }
        if (x >= MOD) {
            x -= MOD;
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(MOD - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, MOD - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = mul(x, rhs.x, MOD);
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
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
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
};

using Z = MInt<MOD>;

struct Comb {
    i64 n;
    std::vector<Z> _fac;
    std::vector<Z> _invfac;
    std::vector<Z> _inv;
    Comb() : n{0}, _fac{1}, _invfac{1}, _inv{0} {}
    Comb(i64 n) : Comb() { init(n); }
    
    void init(i64 m) {
        m = std::min(m, MOD - 1);
        if (m <= n) return;
        _fac.resize(m + 1);
        _invfac.resize(m + 1);
        _inv.resize(m + 1);
        
        for (int i = n + 1; i <= m; i++) {
            _fac[i] = _fac[i - 1] * i;
        }
        _invfac[m] = _fac[m].inv();
        for (int i = m; i > n; i--) {
            _invfac[i - 1] = _invfac[i] * i;
            _inv[i] = _invfac[i] * _fac[i - 1];
        }
        n = m;
    }
    Z fac(i64 m) {
        if (m > n) init(2 * m);
        return _fac[m];
    }
    Z invfac(i64 m) {
        if (m > n) init(2 * m);
        return _invfac[m];
    }
    Z inv(i64 m) {
        if (m > n) init(2 * m);
        return _inv[m];
    }
    Z binom(i64 n, i64 m) {
        if (n < m || m < 0) return 0;
        return fac(n) * invfac(m) * invfac(n - m);
    }
    Z Lucas(Z m, Z n) {
        return n == 0 ? Z(1) : Lucas(m.val() / MOD, n.val() / MOD) * binom(m.val(), n.val());
    }
} comb;

constexpr i64 b = 233;

std::vector<Z> Hash(std::string s) {
    std::vector<Z> ans{0};
    for(auto c : s){
        ans.push_back(ans.back() * b + (c - 'a' + 1));
    }
    return ans;
}

void solve() {
    std::string s;
    std::string sub;
    std::cin >> s >> sub;

    auto a = Hash(s);
    auto q = Hash(sub);
    auto find = q.back();

    int ans = 0;
    int l = 1, r = sub.size(), length = sub.size();
    while (r <= s.size()) {
        if (a[r] - a[l - 1] * power(Z(b), length) == find) {
            ans++;
        }
        l++, r++;
    }
    std::cout << ans << "\n";
}

int main() {
    std::ios_base::sync_with_stdio(0);
    std::cin.tie(nullptr);

    int t = 1;
    // cin >> t;

    while (t--) {
        solve();
    }
}