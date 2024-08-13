#include <bits/stdc++.h>
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
    static ll Mod;
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
    friend constexpr istream &operator>>(istream &is, MInt &a) {
        ll v; is >> v; a = MInt(v); return is;
    }
    friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
        return os << a.x;
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.x == rhs.x;
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.x != rhs.x;
    }
    friend constexpr bool operator<(MInt lhs, MInt rhs) {
        return lhs.x < rhs.x;
    }
};
template<>
ll MInt<0>::Mod = 998244353;
constexpr int P = 1e9 + 7;
using Z = MInt<P>;

template<class T>
struct Matrix {
    int n, m;
    vector<vector<T>> mat;
    constexpr Matrix(int n_, int m_) { init(n_, m_); }
    constexpr Matrix(vector<vector<T>> mat_) { init(mat_); }
    constexpr void init(int n_, int m_) {
        n = n_; m = m_;
        mat.assign(n, vector<T>(m));
    }
    constexpr void init(vector<vector<T>> &mat_) {
        n = mat_.size();
        m = mat_[0].size();
        mat = mat_;
    }
    constexpr Matrix &operator*=(const Matrix &rhs) & {
        assert(mat[0].size() == rhs.mat.size());
        int n = mat.size(), k = mat[0].size(), m = rhs.mat[0].size();
        Matrix ans(n, m);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int l = 0; l < k; l++) {
                    ans.mat[i][j] += mat[i][l] * rhs.mat[l][j];
                }
            }
        }
        mat = ans.mat;
        return *this;
    }
    friend constexpr Matrix operator*(Matrix lhs, const Matrix &rhs) {
        return lhs *= rhs;
    }
};
template<class T>
constexpr Matrix<T> unit(int n) {
    Matrix<T> res(n, n);
    for (int i = 0; i < n; i++) {
        res.mat[i][i] = 1;
    }
    return res;
}
template<class T>
constexpr Matrix<T> power(Matrix<T> a, ll b) {
    assert(a.n == a.m);
    Matrix<T> res = unit<T>(a.n);
    for (; b; b /= 2, a *= a)
        if (b % 2) res *= a;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    Matrix<Z> base(vector<vector<Z>> {{0}, {1}});
    Matrix<Z> trans(vector<vector<Z>> {{0, 1}, {1, 1}});
    base = power(trans, n) * base;
    cout << base.mat[0][0] << "\n";
    
    return 0;
}