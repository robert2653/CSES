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
struct Fenwick {
    int n; vector<T> a;
    Fenwick(int n) : n(n), a(n) {}
    void add(int x, const T &v) {
        for (int i = x + 1; i <= n; i += i & -i)
            a[i - 1] = a[i - 1] + v;
    }
    T sum(int x) {
        T ans{};
        for (int i = x; i > 0; i -= i & -i)
            ans = ans + a[i - 1];
        return ans;
    }
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    int select(const T &k, int start = 0) {
        // 找到最小的 x, 使得 sum(x + 1) - sum(start) > k
        int x = 0; T cur = -sum(start);
        for (int i = 1 << __lg(n); i; i /= 2) {
            if (x + i <= n && cur + a[x + i - 1] <= k) {
                x += i;
                cur = cur + a[x - 1];
            }
        }
        return x;
    }
};

template<class T>
vector<int> dct(vector<T> &a) {
    vector<int> res;
    vector<T> t = a;
    sort(t.begin(), t.end());
    t.resize(unique(t.begin(), t.end()) - t.begin());
    for (auto i : a) {
        res.push_back(lower_bound(t.begin(), t.end(), i) - t.begin() + 1);
    }
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    auto d = dct(a);
    int m = *max_element(d.begin(), d.end());
    Fenwick<Z> f(m + 1);
    f.add(0, 1);
    for (int i = 0; i < n; i++) {
        Z sum = f.sum(d[i]);
        f.add(d[i], sum);
    }
    Z ans = f.sum(m + 1) - 1;
    cout << ans << "\n";
    return 0;
}