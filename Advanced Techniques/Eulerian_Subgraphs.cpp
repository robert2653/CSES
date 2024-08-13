#include <bits/stdc++.h>
// #pragma GCC target("popcnt")
// C++ 20 vector grammer will not work
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

void solve() {
    int n, m; 
    cin >> n >> m;

    vector<int> color(n);
    vector<vector<int>> g(n);
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    int cnt = 0;

    auto dfs = [&](auto self, int x, int p) {
        if (color[x]) return;
        color[x] = 1;
        for (int y : g[x]) {
            if (y == p) continue;
            if (color[y] == 1) {
                ++cnt;
            } else if (color[y] == 0) {
                self(self, y, x);
            }
        }
        color[x] = 2;
    };

    Z ans = 1;
    for (int i = 0; i < n; i++) {
        if (!color[i]) {
            cnt = 0;
            dfs(dfs, i, -1);
            ans *= power(Z(2), cnt);
        }
    }

    cout << ans << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}