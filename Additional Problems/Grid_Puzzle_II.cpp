#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template<class Tf, class Tc>
struct MCMF {
    int n, m;
    Tf INF_FlOW = numeric_limits<Tf>::max() / 2;
    Tc INF_COST = numeric_limits<Tc>::max() / 2;
    struct Edge {
        int from, to;
        Tf flow, cap; // 流量跟容量
        Tc cost;
    };
    vector<vector<int>> adj;
    vector<Edge> edges; // 幫每個 edge 編號
    vector<Tc> dis, pot; // johnson algorithm, using spfa
    vector<int> par; // 路徑恢復
    vector<bool> vis;

    MCMF(int n_ = 0) { init(n_); }
    void init(int n_ = 0) {
        n = n_;
        m = 0;
        edges.clear();
        pot.assign(n, 0);
        adj.assign(n, vector<int>{});
    }

    void add_edge(int u, int v, Tf cap, Tc cost){
        edges.push_back({u, v, 0, cap, cost});
        edges.push_back({v, u, 0, 0, -cost});
        adj[u].push_back(m++);
        adj[v].push_back(m++);
    }

    bool spfa(int s, int t) {
        dis.assign(n, INF_COST);
        par.assign(n, -1);
        vis.assign(n, false);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        vis[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            vis[u] = false;
            for (int id : adj[u]) {
                Edge &e = edges[id];
                int v = e.to;
                if (e.flow < e.cap && dis[v] > dis[u] + e.cost + pot[u] - pot[v]) {
                    dis[v] = dis[u] + e.cost + pot[u] - pot[v];
                    par[v] = id;
                    if (!vis[v]) {
                        q.push(v);
                        vis[v] = true;
                    }
                }
            }
        }
        return dis[t] != INF_COST;
    }
    // 限定 flow, 最小化 cost
    pair<Tf, Tc> work_flow(int s, int t, Tf need = -1) {
        if (need == -1) need = INF_FlOW;
        Tf flow{};
        Tc cost{};
        while (spfa(s, t)) {
            for (int i = 0; i < n; i++) {
                if (dis[i] != INF_COST) pot[i] += dis[i];
            }
            Tf f = INF_FlOW;
            int cur = t;
            while (cur != s) {
                Edge &e = edges[par[cur]];
                f = min(f, e.cap - e.flow);
                cur = e.from;
            }
            f = min<Tf>(f, need);
            flow += f;
            cost += f * (pot[t] - pot[s]);
            need -= f;
            cur = t;
            while (cur != s) {
                Edge &e = edges[par[cur]];
                e.flow += f;
                edges[par[cur] ^ 1].flow -= f;
                cur = e.from;
            }
            if (need == 0) break;
        }
        return make_pair(flow, cost);
    }
    // 限定 cost, 最大化 flow
    pair<Tf, Tc> work_budget(int s, int t, Tc budget = -1) {
        if (budget == -1) budget = INF_COST;
        Tf flow{};
        Tc cost{};
        while (spfa(s, t)) {
            for (int i = 0; i < n; i++) {
                if (dis[i] != INF_COST) pot[i] += dis[i];
            }
            Tf f = INF_FlOW;
            int cur = t;
            while (cur != s) {
                Edge &e = edges[par[cur]];
                f = min(f, e.cap - e.flow);
                cur = e.from;
            }
            f = min<Tf>(f, budget / (pot[t] - pot[s]));
            flow += f;
            cost += f * (pot[t] - pot[s]);
            budget -= f * (pot[t] - pot[s]);
            cur = t;
            while (cur != s) {
                Edge &e = edges[par[cur]];
                e.flow += f;
                edges[par[cur] ^ 1].flow -= f;
                cur = e.from;
            }
            if (budget == 0) break;
        }
        return make_pair(flow, cost);
    }
};

void solve() {
    int n; cin >> n;
    MCMF<int, int> g(n * 2 + 2);
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        g.add_edge(0, i, x, 0);
        sum += x;
    }
    for (int i = 1; i <= n; i++) {
        int x; cin >> x;
        g.add_edge(n + i, n * 2 + 1, x, 0);
        sum += x;
    }

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int cost; cin >> cost;
            g.add_edge(i, n + j, 1, -cost);
        }
    }

    auto [flow, cost] = g.work_flow(0, n * 2 + 1);
    if (flow * 2 == sum) {
        cout << -cost << "\n";
        for (int i = 1; i <= n; i++) {
            for (int id : g.adj[i]) {
                if (id % 2 == 0) {
                    if (g.edges[id].flow == 1) {
                        cout << 'X';
                    } else {
                        cout << '.';
                    }
                }
            }
            cout << "\n";
        }
    } else {
        cout << -1 << "\n";
    }
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