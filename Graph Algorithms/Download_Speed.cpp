#include <bits/stdc++.h>

using namespace std;

template<class T>
struct Dinic {
    struct _Edge {
        int to;
        T f, cap; // 流量跟容量
    };
    int n, m, s, t;
    const T INF_FlOW = 1LL << 60;
    vector<vector<int>> g;
    vector<_Edge> e;
    vector<int> h, cur;
    Dinic(int n_ = 0) { init(n_); }
    void init(int n_) {
        n = n_; m = 0;
        h.resize(n); cur.resize(n);
        g.assign(n, {});
        e.clear();
    }
    void add_edge(int u, int v, T cap) {
        e.push_back({v, 0, cap});
        e.push_back({u, 0, 0});
        g[u].push_back(m++);
        g[v].push_back(m++);
    }
    bool bfs() {
        fill(h.begin(), h.end(), -1);
        h[s] = 0; queue<int> q;
        q.push(s);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int id : g[u]) {
                auto [v, f, cap] = e[id];
                if (f == cap) continue;
                if (h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) return true;
                    q.push(v);
                }
            }
        }
        return false;
    }
    T dfs(int u, T flow) {
        if (flow == 0) return 0;
        if (u == t) return flow;
        for (int &i = cur[u]; i < g[u].size(); i++) {
            int j = g[u][i];
            auto [v, f, cap] = e[j];
            if (h[u] + 1 != h[v]) continue;
            if (f == cap) continue;
            T mn = dfs(v, min(flow, cap - f));
            if (mn > 0) {
                e[j].f += mn;
                e[j ^ 1].f -= mn;
                return mn;
            }
        }
        return 0;
    }
    T work(int s_, int t_) {
        s = s_; t = t_; T f = 0;
        while (bfs()) {
            fill(cur.begin(), cur.end(), 0);
            while (true) {
                T res = dfs(s, INF_FlOW);
                if (res == 0) break;
                f += res;
            }
        }
        return f;
    }
    void reset() {
        for (int i = 0; i < m; i++) e[i].f = 0;
    }
    void reuse(int n_) { // 走殘留網路, res += f
        while (n < n_) {
            g.emplace_back();
            h.emplace_back();
            cur.emplace_back();
            n += 1;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic<long long> dinic(n);

    int src = 0, dst = n - 1;
    for (int i = 0; i < m; i++) {
        int u, v, f;
        cin >> u >> v >> f;
        u--, v--;
        dinic.add_edge(u, v, f);
    }
    cout << dinic.work(src, dst) << "\n";

    return 0;
}