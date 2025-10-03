#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    MCMF<int, int> g(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g.add_edge(u, v, 1, 1);
    }
    int s = 0, t = n - 1;
    auto [flow, cost] = g.work_flow(s, t, k);

    if (flow < k) {
        cout << -1 << "\n";
        return 0;
    }
    cout << cost << "\n";
    for (int i = 0; i < k; i++) {
        vector<int> path;
        int cur = s;
        path.push_back(cur);
        while (cur != t) {
            for (int id : g.g[cur]) {
                if (id % 2 == 0 && g.e[id].f) {
                    g.e[id].f--;
                    cur = g.e[id].to;
                    break;
                }
            }
            path.push_back(cur);
        }
        cout << path.size() << "\n";
        for (auto v : path) {
            cout << v + 1 << " ";
        }
        cout << "\n";
    }

    return 0;
}