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

const ll inf = 1E12;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();

    int t = 1;
    cin >> t;
    vector<ll> v;
    ll cur = 0;
    while (cur <= inf) {
        cur += (v.size() + 1);
        v.push_back(cur);
    }
    cerr << v.size() << "\n";
    while (t--) {
        int ans = 0;
        ll x;
        cin >> x;
        for (int i = v.size() - 1; i >= 0; i--) {
            while (x >= v[i]) {
                x -= v[i];
                ans++;
            }
        }
        cout << ans << "\n";
    }

    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}