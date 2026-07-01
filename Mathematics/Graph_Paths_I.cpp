#include <bits/stdc++.h>
using namespace std;
using ll = long long;

ll mul(ll a, ll b, ll p) { // P 超過 int 再用，慢
    ll res = a * b - ll(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) res += p;
    return res;
}
template<class T> constexpr T power(T a, ll b) {
    T res {1};
    for (; b > 0; b >>= 1, a = a * a)
    if (b & 1) res = res * a;
    return res;
}
template<int P> struct Mint {
    static int Mod;
    static int getMod() { return P > 0 ? P : Mod; }
    static void setMod(int Mod_) { Mod = Mod_; }
    ll x;
    Mint(ll x = 0) : x {norm(x % getMod())} {}
    ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    explicit operator int() const { return x; }
    Mint operator-() const { return getMod() - x; }
    Mint inv() const { return power(*this, getMod() - 2); }
    Mint operator+(Mint a) const { return x + a.x; }
    Mint operator-(Mint a) const { return x - a.x; }
    Mint operator*(Mint a) const { return x * a.x; }
    Mint operator/(Mint a) const { return *this * a.inv(); }
    
    Mint &operator+=(Mint a) { return *this = *this + a; }
    Mint &operator-=(Mint a) { return *this = *this - a; }
    Mint &operator*=(Mint a) { return *this = *this * a; }
    Mint &operator/=(Mint a) { return *this = *this / a; }
    
    friend istream &operator>>(istream &is, Mint &a)
    { ll v; is >> v; a = Mint(v); return is; }
    friend ostream &operator<<(ostream &os, Mint a)
    { return os << a.x; }
    bool operator==(Mint y) const { return x == y.x; }
    bool operator!=(Mint y) const { return x != y.x; }
};
template<> int Mint<0>::Mod = 998244353;
constexpr int P = 1E9 + 7;
using Z = Mint<P>;

using Matrix = vector<vector<Z>>;
Matrix operator*(const Matrix &a, const Matrix &b) {
    int n = a.size(), k = a[0].size(), m = b[0].size();
    assert(k == b.size());
    Matrix res(n, vector<Z>(m));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int l = 0; l < k; l++)
                res[i][j] += a[i][l] * b[l][j];
    return res;
}
Matrix power(Matrix a, ll b) {
    int n = a.size();
    Matrix res(n, vector<Z>(n));
    for (int i = 0; i < n; i++) res[i][i] = 1;
    for (; b > 0; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k; cin >> n >> m >> k;
    vector<vector<Z>> g(n, vector<Z>(n));
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u][v] += 1;
    }
    Matrix mat(g);
    mat = power(mat, k);
    cout << mat[0][n - 1] << "\n";

    return 0;
}