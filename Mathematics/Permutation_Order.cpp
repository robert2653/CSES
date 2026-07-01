#include <bits/stdc++.h>

using namespace std;
using ll = long long;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> void chmin(T &a, const T &b) { if (a > b) a = b; }
template<class T> void chmax(T &a, const T &b) { if (a < b) a = b; }

void solve() {
    vector<ll> fac(20);
    fac[0] = 1;
    for (int i = 1; i < 20; i++) {
        fac[i] = fac[i - 1] * i;
    }
    int t;
    cin >> t;
    while (t--) {
        int op;
        cin >> op;
        if (op == 1) {
            int n;
            ll k;
            cin >> n >> k;
            k--;
            vector<int> ans(n);
            vector<int> vis(n);
            for (int i = 0; i < n; i++) {
                int ord = k / fac[n - 1 - i];
                k %= fac[n - 1 - i];
                for (int j = 0; j < n; j++) {
                    if (!vis[j]) {
                        if (ord == 0) {
                            ans[i] = j;
                            vis[j] = 1;
                            break;
                        }
                        ord--;
                    }
                }
            }
            for (int i = 0; i < n; i++) {
                cout << ans[i] + 1 << " \n"[i == n - 1];
            }
        } else {
            int n;
            cin >> n;
            vector<int> a(n);
            for (int i = 0; i < n; i++) {
                cin >> a[i];
                a[i]--;
            }
            ll k = 1;
            vector<int> vis(n);
            for (int i = 0; i < n; i++) {
                int cnt = 0;
                for (int j = 0; j < a[i]; j++) {
                    if (!vis[j]) {
                        cnt++;
                    }
                }
                k += cnt * fac[n - 1 - i];
                vis[a[i]] = 1;
            }
            cout << k << "\n";
        }
    }
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