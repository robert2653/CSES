// Burnside's Lemma
#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int mod = 1e9 + 7;

struct nCr {
    int mod;
    nCr(int mod) : mod(mod) {};
    int inverse(int num) {
        if (num == 1) return 1;
        return (mod - ((mod / num) * inverse(mod % num)) % mod) % mod;
    }
    int fast_exp(int x, int p) {
        int ans = 1;
        while (p > 0) {
            if (p & 1) ans = (ans * x) % mod;
            x = x * x % mod;
            p >>= 1;
        }
        return ans;
    }
    vector<int> fac;
    void buildFac(int n) {
        fac.resize(n + 1);
        fac[0] = 1;
        for(int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }
    }
    int C(int m, int n) {
        return m < n ? 0 : fac[m] * inverse(fac[n]) % mod * inverse(fac[m - n]) % mod;
    }
    int Lucas(int m, int n) {
        return n == 0 ? 1 % mod : Lucas(m / mod, n / mod) * C(m % mod, n % mod) % mod;
    }
};

void solve(){
    nCr ncr(mod);
    int ans = 0;
    int n, m; cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        int x = ncr.fast_exp(m, __gcd(i, n));
        (x *= ncr.inverse(n)) %= mod;
        (ans += x) %= mod;
    }
    cout << ans << "\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}