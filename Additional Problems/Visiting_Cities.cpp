#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Dominator_tree {
    int n, id;
    vector<vector<int>> adj, radj, bucket;
    vector<int> sdom, dom, vis, rev, pa, rt, mn, res;
    Dominator_tree(int n_ = 0) { init(n_); }
    void init(int _n) {
        n = _n, id = 0;
        adj.assign(n, vector<int>());
        radj.assign(n, vector<int>());
        bucket.assign(n, vector<int>());
        sdom.resize(n);
        dom.assign(n, -1);
        vis.assign(n, -1);
        rev.resize(n);
        pa.resize(n);
        rt.resize(n);
        mn.resize(n);
        res.resize(n);
    }
    void add_edge(int u, int v) { adj[u].push_back(v); }
    int query(int v, int x) {
        if (rt[v] == v) return x ? -1 : v;
        int p = query(rt[v], 1);
        if (p == -1) return x ? rt[v] : mn[v];
        if (sdom[mn[v]] > sdom[mn[rt[v]]]) mn[v] = mn[rt[v]];
        rt[v] = p;
        return x ? p : mn[v];
    }
    void dfs(int v) {
        vis[v] = id, rev[id] = v;
        rt[id] = mn[id] = sdom[id] = id, id++;
        for (int u : adj[v]) {
            if (vis[u] == -1) dfs(u), pa[vis[u]] = vis[v];
            radj[vis[u]].push_back(vis[v]);
        }
    }
    void build(int s) {
        dfs(s);
        for (int i = id - 1; i >= 0; i--) {
            for (int u : radj[i])
                sdom[i] = min(sdom[i], sdom[query(u, 0)]);
            if (i) bucket[sdom[i]].push_back(i);
            for (int u : bucket[i]) {
                int p = query(u, 0);
                dom[u] = sdom[p] == i ? i : p;
            }
            if (i) rt[i] = pa[i];
        }
        res.assign(n, -1);
        for (int i = 1; i < id; i++)
            if (dom[i] != sdom[i]) dom[i] = dom[dom[i]];
        for (int i = 1; i < id; i++) res[rev[i]] = rev[dom[i]];
        res[s] = s;
        for (int i = 0; i < n; i++) dom[i] = res[i];
    }
};


int main() {
    int n, m; cin >> n >> m;
    vector<vector<pair<int, ll>>> adj(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        ll w;
        cin >> w;
        adj[u].emplace_back(v, w);
    }
    vector<pair<int, int>> crit;
    priority_queue<pair<ll, int>, vector<pair<ll, int>>, greater<pair<ll, int>>> pq;
    vector<ll> dis(n, 4e18);
    dis[0] = 0;
    pq.emplace(0, 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d > dis[u]) continue;
        for (auto [v, w] : adj[u]) {
            if (dis[u] + w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.emplace(dis[v], v);
            }
        }
    }
    // if (dis[n - 1] == 4e18) {
    //     cout << -1 << "\n";
    //     return 0;
    // }
    for (int u = 0; u < n; u++){
        for (auto [v, w] : adj[u]){
            if (dis[u] + w == dis[v]) {
                crit.emplace_back(u, v);
            }
        }
    }
    Dominator_tree dt;
    dt.init(n);
    for (auto [u, v] : crit) {
        dt.add_edge(u, v);
    }
    dt.build(0);

    vector<int> ans;
    // for (int i = n - 1; i != 0; i = dt.dom[i]) {
    //     ans.push_back(i + 1);
    // }
    // ans.push_back(1);
    for (int i = 0; i < n; i++) {
        if (dt.dom[i] != -1) {
            ans.push_back(i);
        }
    }
    sort(ans.begin(), ans.end());

    cout << ans.size() << "\n";
    for (int i : ans) {
        cout << i << " ";
    }
    cout << "\n";
    
    return 0;
}