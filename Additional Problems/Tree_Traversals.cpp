#include <bits/stdc++.h>
using namespace std;

int p = 0;
int pre[100000], in[100000];
void dfs(int l, int r) {
    int now = pre[p], mid = in[now];
    if (mid > l) {
        p++;
        dfs(l, mid - 1);
    }
    if (mid < r) {
        p++;
        dfs(mid + 1, r);
    }
    cout << now + 1 << " ";
}

void solve() {
    int n; cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> pre[i];
        pre[i]--;
    }
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        x--;
        in[x] = i;
    }
    dfs(0, n - 1);
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}