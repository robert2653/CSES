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
int inv(int a) {
    return power(a, Mod - 2);
}
int Div(int a, int b) {
    return mul(a, inv(b));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();
    vector<int> fac(n + 1, 1);
    for (int i = 1; i <= n; i++) {
        fac[i] = mul(fac[i - 1], i);
    }
    vector<vector<int>> dp(n, vector<int>(n));
    auto len = [&](int i, int j) {
        return (j - i + 1) / 2;
    };
    vector<vector<int>> C(n + 1, vector<int>(n + 1));
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) {
            C[i][j] = add(C[i - 1][j - 1], C[i - 1][j]);
        }
    }
    for (int i = n - 1; i >= 0; i--) {
        for (int j = i + 1; j < n; j += 2) {
            if (i + 1 == j) {
                if (s[i] == s[j]) {
                    dp[i][j] = 1;
                }
                // cerr << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
                continue;
            }
            for (int k = i + 1; k <= j; k += 2) {
                if (s[i] == s[k]) {
                    int x;
                    if (i + 1 > k - 1) x = 1;
                    else x = dp[i + 1][k - 1];
                    int y;
                    if (k + 1 > j) y = 1;
                    else y = dp[k + 1][j];
                    int z = C[len(i, j)][len(i, k)];
                    dp[i][j] = add(dp[i][j], mul(mul(x, y), z));
                }
            }
            // cerr << "dp[" << i << "][" << j << "] = " << dp[i][j] << "\n";
        }
    }
    cout << dp[0][n - 1] << "\n";
    return 0;
}