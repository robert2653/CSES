#include <bits/stdc++.h>

using ll = long long;
using namespace std;

template<class Tf, class Tc>
struct MCMF {
    struct _Edge {
        int to;
        Tf f, cap; // 流量跟容量
        Tc cost;
    };
    int n, m, s, t;
    const Tf INF_FLOW = 1 << 30;
    const Tc INF_COST = 1 << 30;
    vector<_Edge> e;
    vector<vector<int>> g;
    vector<Tc> dis;
    vector<int> rt, inq;
    MCMF(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_; m = 0;
        e.clear();
        g.assign(n, {});
    }
    void add_edge(int u, int v, Tf cap, Tc cost) {
        e.push_back({v, 0, cap, cost});
        e.push_back({u, 0, 0, -cost});
        g[u].push_back(m++);
        g[v].push_back(m++);
    }
    bool spfa() {
        dis.assign(n, INF_COST);
        rt.assign(n, -1), inq.assign(n, 0);
        queue<int> q; q.push(s);
        dis[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            inq[u] = 0;
            for (int id : g[u]) {
                auto [v, f, cap, cost] = e[id];
                Tc ndis = dis[u] + cost;
                if (f < cap && dis[v] > ndis) {
                    dis[v] = ndis, rt[v] = id;
                    if (!inq[v])
                        q.push(v), inq[v] = 1;
                }
            }
        }
        return dis[t] != INF_COST;
    }
    // 限定 flow, 最小化 cost
    pair<Tf, Tc> work_flow(int s_, int t_, Tf need) {
        s = s_, t = t_;
        Tf flow{}; Tc cost{};
        while (spfa()) {
            Tf f = need;
            for (int i = t; i != s; i = e[rt[i] ^ 1].to)
                f = min(f, e[rt[i]].cap - e[rt[i]].f);
            for (int i = t; i != s; i = e[rt[i] ^ 1].to)
                e[rt[i]].f += f, e[rt[i] ^ 1].f -= f;
            flow += f, need -= f;
            cost += f * dis[t];
            if (need == 0) break;
        }
        return {flow, cost};
    }
    // 限定 cost, 最大化 flow
    pair<Tf, Tc> work_budget(int s_, int t_, Tc budget) {
        s = s_, t = t_;
        Tf flow{}; Tc cost{};
        while (spfa()) {
            Tf f = budget / dis[t];
            for (int i = t; i != s; i = e[rt[i] ^ 1].to)
                f = min(f, e[rt[i]].cap - e[rt[i]].f);
            for (int i = t; i != s; i = e[rt[i] ^ 1].to)
                e[rt[i]].f += f, e[rt[i] ^ 1].f -= f;
            flow += f, budget -= f * dis[t];
            cost += f * dis[t];
            if (budget == 0 || f == 0) break;
        }
        return {flow, cost};
    }
    void reset() {
        for (int i = 0; i < m; i++) e[i].f = 0;
    }
};

void solve() {
    int n; cin >> n;
    int s = 0, t = n * 2 + 1;
    MCMF<int, int> g(n * 2 + 2);
    for (int i = 1; i <= n; i++) {
        g.add_edge(s, i, 1, 0);
        g.add_edge(n + i, t, 1, 0);
    }
    // stuff to task
    for (int i = 1; i <= n; i++) { // stuff
        for (int j = n + 1; j <= 2 * n; j++) { // task
            int cost; cin >> cost;
            g.add_edge(i, j, 1, cost);
        }
    }
    auto [flow, cost] = g.work_flow(s, t, g.INF_FLOW);
    // output: stuff -> task
    cout << cost << "\n";
    vector<int> ans;
    for (int i = 1; i <= n; i++) { // i is stuff
        for (int id : g.g[i]) {
            auto &e = g.e[id];
            if (e.f == 1) {
                ans.push_back(e.to - n);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        cout << i + 1 << " " << ans[i] << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}