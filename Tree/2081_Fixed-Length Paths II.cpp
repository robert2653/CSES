#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// vector<int> cnt; // 當前深度數量
ll ans = 0;
int mx_depth = 0, subtree_depth = 0;
int l; int r;
vector<int> cnt, tot_cnt;

struct centroid_decomposition {
    int n;
    vector<vector<int>> adj;
    vector<bool> vis;
    vector<int> siz;
    centroid_decomposition() {}
    centroid_decomposition(int n_) { init(n_); }
    void init(int n_) {
        n = n_;
        adj.assign(n, {});
        vis.assign(n, false);
        siz.assign(n, 1);
    }
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    void get_siz(int x, int p = -1, int dep = 0) {
        subtree_depth = max(dep, subtree_depth); // add
        siz[x] = 1;
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            get_siz(y, x, dep + 1);
            siz[x] += siz[y];
        }
    }
    int get_cen(int x, int sz, int p = -1) {
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            if (siz[y] * 2 > sz) {
                return get_cen(y, sz, x);
            }
        }
        return x;
    }

    void get_cnt(int x, int p, int dep = 1) {
        if (dep > r) return;
        subtree_depth = max(dep, subtree_depth);
        cnt[dep]++;
        for (int y : adj[x]) {
            if (y == p || vis[y]) continue;
            get_cnt(y, x, dep + 1);
        }
    }

    void work(int x = 0) {
        subtree_depth = 0;
        get_siz(x);
        int cen = get_cen(x, siz[x]);
        vis[cen] = true;
        if (subtree_depth * 2 < l) return; // 剪枝
        mx_depth = 0;
        // do something
	    ll partial_sum_init = (l == 1);
        for (int y : adj[cen]) {
            if (vis[y]) continue;
            subtree_depth = 0;
            get_cnt(y, cen, 1);

            ll partial_sum = partial_sum_init; // 長度在 [l - depth, r - depth] 的數量
			for (int depth = 1; depth <= subtree_depth; depth++) {
				ans += partial_sum * cnt[depth];
				if (r - depth >= 0) partial_sum -= tot_cnt[r - depth];
				if (l - depth - 1 >= 0) partial_sum += tot_cnt[l - depth - 1];
			}

			for (int depth = l - 1; depth <= r - 1 && depth <= subtree_depth;
			    depth++)
				partial_sum_init += cnt[depth];

			for (int depth = 1; depth <= subtree_depth; depth++)
				tot_cnt[depth] += cnt[depth]; // 更新 tot

			mx_depth = max(mx_depth, subtree_depth);
			fill(cnt.begin(), cnt.begin() + subtree_depth + 1, 0);
        }
        fill(tot_cnt.begin() + 1, tot_cnt.begin() + mx_depth + 1, 0);

        for (int y : adj[cen]) {
            if (vis[y]) continue;
            work(y);
        }
    }
};

void solve() {
    int n; cin >> n;
    centroid_decomposition g;
    cin >> l >> r;
    g.init(n);

    for (int i = 1; i < n; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g.addEdge(u, v);
    }
    cnt.assign(n + 1, 0);
    tot_cnt.assign(n + 1, 0);
    tot_cnt[0] = 1;
    g.work(0);

    cout << ans << "\n";
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    // freopen("1.in", "r", stdin);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}