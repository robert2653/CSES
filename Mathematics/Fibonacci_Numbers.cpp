#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mul(ll a, ll b, ll p) {
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
// 改 MLong: getMod() < (1ULL << 31)，會爆用 mul
template<class T>
constexpr T power(T a, ll b) {
    T res {1};
    for (; b > 0; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}
template<int P>
struct Mint {
    static int Mod;
    static int getMod()
    { return P > 0 ? P : Mod; }
    static void setMod(int Mod_)
    { Mod = Mod_; }
    ll x;
    Mint(ll x = 0) : x {norm(x % getMod())} {}
    ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    explicit operator int() const { return x; }
    Mint operator-() const
    { return Mint(norm(getMod() - x)); }
    Mint inv() const
    { return power(*this, getMod() - 2); }
    Mint operator+(Mint rhs) const
    { return Mint(norm(x + rhs.x)); }
    Mint operator-(Mint rhs) const
    { return Mint(norm(x - rhs.x)); }
    Mint operator*(Mint rhs) const
    { return Mint(mul(x, rhs.x, getMod())); }
    Mint operator/(Mint rhs) const
    { return *this * rhs.inv(); }
    friend istream &operator>>(istream &is, Mint &a)
    { ll v; is >> v; a = Mint(v); return is; }
    friend ostream &operator<<(ostream &os, Mint a)
    { return os << a.x; }
    bool operator==(Mint y) const { return x == y.x; }
    bool operator!=(Mint y) const { return x != y.x; }
};
template<>
int Mint<0>::Mod = 998244353;
constexpr int P = 1E9 + 7;
using Z = Mint<P>;

template<class T>
vector<vector<T>> operator*(const vector<vector<T>> &a, const vector<vector<T>> &b) {
    int n = a.size(), k = a[0].size(), m = b[0].size();
    assert(k == b.size()); // 確保內部維度相符
    vector<vector<T>> res(n, vector<T>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int l = 0; l < k; l++)
                res[i][j] = res[i][j] + a[i][l] * b[l][j];
    return res;
}
template<class T>
vector<vector<T>> unit(int n) {
    vector<vector<T>> res(n, vector<T>(n));
    for (int i = 0; i < n; i++)
        res[i][i] = 1;
    return res;
}
template<class T>
vector<vector<T>> power(vector<vector<T>> a, ll b) {
    int n = a.size();
    assert(n == a[0].size());
    auto res = unit<T>(n);
    for (; b; b /= 2, a = a * a)
        if (b % 2) res = res * a;
    return res;
}
Z sum(const vector<vector<Z>> &a) {
    Z res = 0;
    const Z x = 1;
    for (const auto &row : a)
        for (const auto &val : row) {
            const Z const_obj = 5;
            bool result = res == x;  // 这会编译失败！
            res = res + val;
        }
    return res;
}

using Matrix = vector<vector<Z>>;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll n; cin >> n;
    Matrix base {{0}, {1}};
    Matrix trans {{0, 1}, {1, 1}};
    base = power(trans, n) * base;
    cout << base[0][0] << "\n";
    cout << sum(base) << "\n";
    
    return 0;
}