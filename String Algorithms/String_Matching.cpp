#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// template<class T>
// constexpr T power(T a, ll b) {
//     T res {1};
//     for (; b; b /= 2, a *= a)
//         if (b % 2) res *= a;
//     return res;
// }
// constexpr ll mul(ll a, ll b, ll p) {
//     ll res = a * b - ll(1.L * a * b / p) * p;
//     res %= p;
//     if (res < 0) res += p;
//     return res;
// }
// template<ll P>
// struct MInt {
//     ll x;
//     constexpr MInt() : x {0} {}
//     constexpr MInt(ll x) : x {norm(x % getMod())} {}
//     static ll Mod;
//     constexpr static ll getMod() {
//         if (P > 0) return P;
//         else return Mod;
//     }
//     constexpr static void setMod(ll Mod_) {
//         Mod = Mod_;
//     }
//     constexpr ll norm(ll x) const {
//         if (x < 0) x += getMod();
//         if (x >= getMod()) x -= getMod();
//         return x;
//     }
//     constexpr ll val() const { return x; }
//     constexpr MInt operator-() const {
//         MInt res;
//         res.x = norm(getMod() - x);
//         return res;
//     }
//     constexpr MInt inv() const {
//         return power(*this, getMod() - 2);
//     }
//     constexpr MInt &operator*=(MInt rhs) & {
//         if (getMod() < (1ULL << 31)) {
//             x = x * rhs.x % int(getMod());
//         } else {
//             x = mul(x, rhs.x, getMod());
//         }
//         return *this;
//     }
//     constexpr MInt &operator+=(MInt rhs) & {
//         x = norm(x + rhs.x);
//         return *this;
//     }
//     constexpr MInt &operator-=(MInt rhs) & {
//         x = norm(x - rhs.x);
//         return *this;
//     }
//     constexpr MInt &operator/=(MInt rhs) & {
//         return *this *= rhs.inv();
//     }
//     friend constexpr MInt operator*(MInt lhs, MInt rhs) {
//         MInt res = lhs; return res *= rhs;
//     }
//     friend constexpr MInt operator+(MInt lhs, MInt rhs) {
//         MInt res = lhs; return res += rhs;
//     }
//     friend constexpr MInt operator-(MInt lhs, MInt rhs) {
//         MInt res = lhs; return res -= rhs;
//     }
//     friend constexpr MInt operator/(MInt lhs, MInt rhs) {
//         MInt res = lhs; return res /= rhs;
//     }
//     friend constexpr istream &operator>>(istream &is, MInt &a) {
//         ll v; is >> v; a = MInt(v); return is;
//     }
//     friend constexpr ostream &operator<<(ostream &os, const MInt &a) {
//         return os << a.val();
//     }
//     friend constexpr bool operator==(MInt lhs, MInt rhs) {
//         return lhs.val() == rhs.val();
//     }
//     friend constexpr bool operator!=(MInt lhs, MInt rhs) {
//         return lhs.val() != rhs.val();
//     }
//     friend constexpr bool operator<(MInt lhs, MInt rhs) {
//         return lhs.val() < rhs.val();
//     }
// };
// template<>
// ll MInt<0>::Mod = 998244353;
// constexpr int P = 1e9 + 7;
// using Z = MInt<P>;

// constexpr int B = 59;

// vector<Z> Hash(string &s) {
//     vector<Z> ans {0};
//     for (auto c : s) {
//         ans.push_back(ans.back() * B + (c - 'a' + 1));
//     }
//     return ans;
// }

struct KMP {
    string sub;
    vector<int> fail;
    // fail 存匹配失敗時，移去哪
    // 也就是 sub(0, i) 的最長共同前後綴長度
    KMP() {}
    KMP(const string &sub_) {
        build(sub_);
    }
    vector<int> build(const string &sub_) {
        sub = sub_, fail.resize(sub.size(), -1);
        for (int i = 1; i < sub.size(); i++) {
            int now = fail[i - 1];
            while (now != -1 && sub[now + 1] != sub[i]) {
                now = fail[now];
            }
            if (sub[now + 1] == sub[i]) {
                fail[i] = now + 1;
            }
        }
        return fail;
    }
    vector<int> match(const string &s) {
        vector<int> match;
        for (int i = 0, now = -1; i < s.size(); i++) {
            // now 是成功匹配的長度 -1
            while (s[i] != sub[now + 1] && now != -1)
                now = fail[now];
            if (s[i] == sub[now + 1]) now++;
            if (now + 1 == sub.size()) {
                match.push_back(i - now);
                now = fail[now];
            }
        }
        return match;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s, sub;
    cin >> s >> sub;

    // auto a = Hash(s);
    // auto q = Hash(sub);
    // auto find = q.back();
    // int ans = 0;
    // int l = 1, r = sub.size(), len = sub.size();
    // while (r <= s.size()) {
    //     if (a[r] - a[l - 1] * power(Z(B), len) == find) {
    //         ans++;
    //     }
    //     l++, r++;
    // }
    // cout << ans << "\n";

    KMP kmp(sub);
    cout << kmp.match(s).size() << "\n";

    return 0;    
}