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

    // int n; cin >> n;
    // vector<int> a(n);
    // map<int, int> mp;
    // for (int i = 0; i < n; i++) {
    //     cin >> a[i]; mp[a[i]]++;
    // }
    // int m = __lg(*max_element(a.begin(), a.end())) + 1;
    // vector<array<ll, 2>> dp(1 << m);
    // for (int i = 0; i < n; i++) dp[a[i]][0]++, dp[a[i]][1]++;
    // for (int i = 0; i < m; i++) {
    //     for (int mask = 0; mask < 1 << m; mask++) {
    //         if (mask >> i & 1) {
    //             int pre = mask ^ (1 << i);
    //             dp[mask][0] += dp[pre][0];
    //             dp[pre][1] += dp[mask][1];
    //         }
    //     }
    // }
    // for (int i = 0; i < n; i++) {
    //     cout << dp[a[i]][0] << " " << dp[a[i]][1] << " " << n - (dp[((1 << m) - 1) ^ a[i]][0]) << "\n";
    // }
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int m = __lg(*max_element(a.begin(), a.end())) + 1;
    // 定義 dp[mask] 為 mask 被包含於 a[i] 的 i 個數
    vector<Z> dp(1 << m);
    for (int i = 0; i < n; i++) dp[a[i]] += 1;
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[pre] += dp[mask];
            }
        }
    }
    for (int i = 0; i < 1 << m; i++) {
        dp[i] = power(Z(2), int(dp[i])) - 1;
    }
    // 排容，dp[i]: & 起來為 i 的集合數
    for (int i = 0; i < m; i++) {
        for (int mask = 0; mask < 1 << m; mask++) {
            if (mask >> i & 1) {
                int pre = mask ^ (1 << i);
                dp[pre] -= dp[mask];
            }
        }
    }
    for (int i = 0; i <= n; i++) {
        cout << dp[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}