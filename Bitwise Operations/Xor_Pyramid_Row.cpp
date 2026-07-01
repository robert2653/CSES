#include <bits/stdc++.h>

using namespace std;
int read() {
    int x = 0; char ch = getchar();
    while (!isdigit(ch)) { ch = getchar(); }
    while (isdigit(ch)) { x = x * 10 + ch - '0'; ch = getchar(); }
    return x;
}
void write(int x) {
    if (x >= 10) write(x / 10);
    putchar(x % 10 + '0');
}

const int N = 200000;
int dp[N];
int main() {
    int n = read(), k = read();
    for (int i = 0; i < n; i++) {
        dp[i] = read();
    }
    int m = n - k;
    int lg = __lg(n) + 1;
    // v_i = Xor_{j \in m}(a_{i+j})
    for (int i = 0; i < lg; i++) {
        if (m >> i & 1) {
            int b = 1 << i;
            for (int j = 0; j + b < n; j++) {
                dp[j] ^= dp[j + b];
            }
        }
    }
    for (int i = 0; i < k; i++) {
        write(dp[i]);
        putchar(" \n"[i == k - 1]);
    }
    return 0;
}