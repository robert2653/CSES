#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

const int Mod = 1E9 + 7;
int add(int a, int b) { return (a + b) % Mod; }
int mul(int a, int b) { return 1LL * a * b % Mod; }
int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1) {
        if (b & 1) res = mul(res, a);
        a = mul(a, a);
    }
    return res;
}
vector<int> minp, prime;
void sieve(int n) {
    minp.resize(n + 1);
    for (int i = 2; i <= n; i++) {
        if (!minp[i]) {
            minp[i] = i;
            prime.push_back(i);
        }
        for (int p : prime) {
            if (i * p > n) break;
            minp[i * p] = p;
            if (minp[i] == p) break;
        }
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i]--;
    }
    vector<int> b;
    vector<int> vis(n);
    map<int, int> mp;
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            int u = i;
            int len = 0;
            while (!vis[u]) {
                vis[u] = 1;
                u = a[u];
                len++;
            }
            while (len > 1) {
                int p = minp[len];
                int cnt = 0;
                while (minp[len] == p) {
                    cnt++;
                    len /= p;
                }
                mp[p] = max(mp[p], cnt);
            }
        }
    }
    int lcm = 1;
    for (auto [p, cnt] : mp) {
        lcm = mul(lcm, power(p, cnt));
    }
    cout << lcm << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    auto s = chrono::high_resolution_clock::now();

    sieve(200000);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }

    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    
    return 0;
}