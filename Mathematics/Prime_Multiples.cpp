#include <bits/stdc++.h>
using namespace std;
// 數 n 以下有多少數可以被一些質數整除，用排容即可
#define int long long
signed main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, k;
    cin >> n >> k;
    vector<int> primes(k);
    for(int i = 0; i < k; i++) cin >> primes[i];
 
    int ans = 0;
 
    for (int mask = 1; mask < (1 << k); mask++) {
        int cur = n;
        for (int bit = 0; bit < k; bit ++) {
            if (mask >> bit & 1) {
                cur /= primes[bit];
            }
        }
        if (__builtin_popcount(mask) % 2 == 1) ans += cur;
        else ans -= cur;
    }
    cout << ans <<"\n";
}