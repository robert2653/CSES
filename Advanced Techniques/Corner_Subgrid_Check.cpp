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

const int N = 3000;
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    auto s = chrono::high_resolution_clock::now();

    int n, k;
    cin >> n >> k;
    vector<string> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int c = 0; c < k; c++) {
        bitset<N> vis[n];
        bool ans = false;
        for (int i = 0; i < n; i++) {
            vector<int> p;
            for (int j = 0; j < n; j++) {
                if (a[i][j] == 'A' + c) {
                    p.push_back(j);
                }
            }
            int m = p.size();
            for (int x = 0; x < m; x++) {
                for (int y = x + 1; y < m; y++) {
                    if (vis[p[x]][p[y]]) {
                        ans = true;
                        goto print;
                    } else {
                        vis[p[x]][p[y]] = true;
                    }
                }
            }
        }
        print:
        cout << (ans ? "YES\n" : "NO\n");
    }
    auto e = chrono::high_resolution_clock::now();
    cerr << chrono::duration_cast<chrono::milliseconds>(e - s).count() << " ms\n";
    return 0;
}