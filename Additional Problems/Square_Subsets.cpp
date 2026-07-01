#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

const int Mod = 1E9 + 7;
int add(int a, int b) {
    return (a + b) % Mod;
}
int mul(int a, int b) {
    return 1LL * a * b % Mod;
}
int power(int a, int b) {
    int res = 1;
    for (; b; b >>= 1, a = mul(a, a)) {
        if (b & 1) res = mul(res, a);
    }
    return res;
}

const int N = 5000;
const int P = 669;
int siz = 0;
vector<bitset<P>> bas(P);
void add(bitset<P> &a) {
    if (siz == P) {
        return;
    }
    for (int i = 0; i < P; i++) {
        if (a[i]) {
            if (bas[i].none()) {
                bas[i] = a;
                siz++;
                return;
            }
            a ^= bas[i];
        }
    }
}
void solve() {
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    vector<int> minp(N + 1), primes;
    for (int i = 2; i <= N; i++) {
        if (!minp[i]) {
            minp[i] = i;
            primes.push_back(i);
        }
        for (int p : primes) {
            if (i * p > N) break;
            minp[i * p] = p;
            if (minp[i] == p) break;
        }
    }
    cerr << primes.size() << "\n";
    for (int i = 0; i < n; i++) {
        bitset<P> bs;
        for (int j = 0; j < P; j++) {
            int p = primes[j];
            while (a[i] % p == 0) {
                a[i] /= p;
                bs[j].flip();
            }
        }
        add(bs);
    }
    cout << power(2, n - siz) << "\n";
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