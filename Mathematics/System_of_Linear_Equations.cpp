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
    for (; b; b /= 2, a *= a)
        if (b & 1) res *= a;
    return res;
}
template<int P>
struct Mint {
    // Dynamic Mint, not necessary
    static int Mod;
    static int getMod() {
        return P > 0 ? P : Mod;
    }
    static void setMod(int Mod_) {
        Mod = Mod_;
    }

    ll x;
    Mint(ll x = 0) : x {norm(x % getMod())} {}
    ll norm(ll x) const {
        if (x < 0) x += getMod();
        if (x >= getMod()) x -= getMod();
        return x;
    }
    explicit operator int() const { return x; }
    Mint operator-() const {
        return Mint(norm(getMod() - x));
    }
    Mint inv() const {
        return power(*this, getMod() - 2);
    }
    Mint &operator+=(Mint rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    Mint &operator-=(Mint rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    Mint &operator*=(Mint rhs) & {
        x = x * rhs.x % getMod();
        return *this;
    }
    Mint &operator/=(Mint rhs) & {
        return *this *= rhs.inv();
    }
    friend Mint operator+(Mint lhs, Mint rhs) {
        return lhs += rhs;
    }
    friend Mint operator-(Mint lhs, Mint rhs) {
        return lhs -= rhs;
    }
    friend Mint operator*(Mint lhs, Mint rhs) {
        return lhs *= rhs;
    }
    friend Mint operator/(Mint lhs, Mint rhs) {
        return lhs /= rhs;
    }
    friend istream &operator>>(istream &is, Mint &a) {
        ll v; is >> v; a = Mint(v); return is;
    }
    friend ostream &operator<<(ostream &os, const Mint &a) {
        return os << a.x;
    }
    // following operators are not necessary
    friend bool operator==(Mint lhs, Mint rhs) {
        return lhs.x == rhs.x;
    }
    friend bool operator!=(Mint lhs, Mint rhs) {
        return lhs.x != rhs.x;
    }
    friend bool operator<(Mint lhs, Mint rhs) {
        return lhs.x < rhs.x;
    }
};
template<>
int Mint<0>::Mod = 998244353;
constexpr int P = 1E9 + 7;
using Z = Mint<P>;

template<class T>
tuple<int, vector<T>, vector<vector<T>>> findBasis(vector<vector<T>> a) {
    int n = a.size(), m = a[0].size(), rk = 0;
    vector<int> pos(m - 1, -1);
    for (int c = 0; c < m - 1; c++) {
        int p = -1;
        for (int r = rk; r < n; r++) {
            if (a[r][c] != 0) {
                p = r;
                break;
            }
        }
        if (p == -1) continue;
        if (p != rk) swap(a[rk], a[p]);
        pos[c] = rk;
        T inv = 1 / a[rk][c];
        for (int j = c; j < m; j++) a[rk][j] *= inv;
        for (int r = 0; r < n; r++) {
            if (r == rk || a[r][c] == 0) continue;
            T fac = a[r][c];
            for (int j = c; j < m; j++)
                a[r][j] -= fac * a[rk][j];
        }
        rk++;
    }
    vector<T> sol(m - 1);
    vector<vector<T>> basis;
    for (int r = rk; r < n; r++)
        if (a[r][m - 1] != 0)
            return {-1, sol, basis};
    for (int c = 0; c < m - 1; c++)
        if (pos[c] != -1)
            sol[c] = a[pos[c]][m - 1];
    for (int c = 0; c < m - 1; c++)
        if (pos[c] == -1) {
            vector<T> v(m - 1);
            v[c] = 1;
            for (int j = 0; j < m - 1; j++)
                if (pos[j] != -1)
                    v[j] = -a[pos[j]][c];
            basis.push_back(v);
        }
    return {rk, sol, basis};
}
template<class T>
using Matrix = vector<vector<T>>;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Matrix<Z> a(n, vector<Z>(m + 1));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m + 1; j++) {
            cin >> a[i][j];
        }
    }
    auto [rk, sol, basis] = findBasis(a);
    if (rk > m || rk == -1) {
        cout << -1 << "\n";
    } else {
        for (int i = 0; i < m; i++) {
            cout << sol[i] << " \n"[i == m - 1];
        }
    }
    return 0;
}