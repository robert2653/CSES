#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int N = 19;
vector<vector<ll>> memo(N + 1, vector<ll>(11, -1));
ll solve(ll n) {
    vector<int> a {0};
    ll tmp = n;
    while (tmp) {
        a.push_back(tmp % 10);
        tmp /= 10;
    }
    n = tmp;
    int len = a.size() - 1;
    // 當前 digit 不會有貢獻，交給 dfs 處理答案就好
    auto dfs = [&](auto self, int p, int prv, bool f0, bool lim) -> ll {
        if (!p) { // 記得想好要回傳 0 還是 1
            return 1;
        }
        if (!lim && !f0 && memo[p][prv] != -1) {
            return memo[p][prv];
        }
        ll res = 0;
        int lst = lim ? a[p] : 9; // or 1 for binary
        for (int i = 0; i <= lst; i++) {
            if (i == prv) continue;
            bool nlim = lim && i == lst;
            if (f0 && i == 0) { // 處理前導零
                res += self(self, p - 1, 10, true, nlim);
            } else {
                res += self(self, p - 1, i, false, nlim);
            }
        }
        if (!lim) memo[p][prv] = res;
        return res;
    };
    return dfs(dfs, len, 10, true, true);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    ll a, b;
    cin >> a >> b;
    cout << solve(b) - solve(a - 1) << "\n";

    return 0;
}