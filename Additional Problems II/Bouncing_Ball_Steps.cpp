#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int Mod = 1E9 + 7;
int add(int a, int b) { a += b; if (a >= Mod) a -= Mod; return a; }
int sub(int a, int b) { a -= b; if (a < 0) a += Mod; return a; }
int mul(int a, int b) { return 1LL * a * b % Mod; }
int power(int a, ll b) {
    int ans = 1;
    for (; b > 0; b >>= 1, a = mul(a, a))
        if (b & 1) ans = mul(ans, a);
    return ans;
}

ll lcm(ll a, ll b) {
    return a * b / __gcd(a, b);
}
void solve() {
    ll n, m, k;
    cin >> n >> m >> k;
    n--;
    m--;
    ll t = k / n + k / m - (k / lcm(n, m));
    ll x = 1 + k % (n * 2);
    ll y = 1 + k % (m * 2);
    if (x > n + 1) {
        x = n * 2 + 2 - x;
    }
    if (y > m + 1) {
        y = m * 2 + 2 - y;
    }
    cout << x << " " << y << " " << t << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}