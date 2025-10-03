// Dinic
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
struct Dinic {
    struct Edge {
        int to;
        T f, cap; // 流量跟容量
    };
    int n, m, s, t;
    const T INF_FlOW = numeric_limits<T>::max();
    vector<vector<int>> g;
    vector<Edge> e;
    vector<int> h, cur;
    Dinic(int n) : n(n), m(0), g(n), h(n), cur(n) {}
    void addEdge(int u, int v, T cap) {
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
    void reuse(int n_) { // 走殘留網路, res += f
        while (n < n_) {
            g.emplace_back();
            h.emplace_back();
            cur.emplace_back();
            n += 1;
        }
    }
};

void solve(int n, int m, Dinic<int> d) {
    int ans = d.work(0, n - 1);
    cout << ans << "\n";
    vector<int> vis(n);
    auto dfs = [&](auto self, int u) -> void {
        if (!vis[u]) {
            vis[u] = 1;
            for (int id : d.g[u]) {
                auto [to, f, cap] = d.e[id];
                if (cap - f > 0) {
                    self(self, to);
                }
            }
        }
    };
    dfs(dfs, 0);
    for (int i = 0; i < n; i++) {
        if (!vis[i]) continue;
        for (int id : d.g[i]) {
            if (id & 1) continue;
            auto e = d.e[id];
            if (!vis[e.to]) {
                cout << i + 1 << " " << e.to + 1 << "\n";
            }
        }
    }
}

int main(){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    Dinic<int> d(n);
    for (int i = 0; i < m; i++) {
        int u, v, cap = 1;
        cin >> u >> v;
        u--; v--;
        d.addEdge(u, v, cap);
        d.addEdge(v, u, cap);
    }
    solve(n, m, d);

    return 0;
}