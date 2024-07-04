#include <bits/stdc++.h>

using namespace std;
using ll = long long;

template <class Info>
struct Seg {    // 左開右閉寫法
    int n;
    vector<Info> info;
    Seg() : n(0) {}
    Seg(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template <class T>
    Seg(vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(vector(n_, v_));
    }
    template <class T>
    void init(vector<T> init_) {
        n = init_.size();
        info.assign(4 << __lg(n), Info());
        function <void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];
                return;
            }
            int m = (l + r) / 2;
            build(p * 2, l, m);
            build(p * 2 + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) { info[p] = info[p * 2] + info[p * 2 + 1]; }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &i) {
        modify(1, 0, n, p, i);
    }
    Info query(int p, int l, int r, int ql, int qr) {
        if (qr <= l || ql >= r) return Info();
        if (ql <= l && r <= qr) return info[p];
        int m = (l + r) / 2;
	    return query(p * 2, l, m, ql, qr) + query(p * 2 + 1, m, r, ql, qr);
    }
    Info query(int ql, int qr) { return query(1, 0, n, ql, qr); }
    template<class F>   // 尋找區間內，第一個符合條件的
    int findFirst(int p, int l, int r, int x, int y, F &&pred) {
        if (l >= y || r <= x) {
            return -1;
        }
        if (l >= x && r <= y && !pred(info[p])) {
            return -1;
        }
        if (r - l == 1) {
            return l;
        }
        int m = (l + r) / 2;
        int res = findFirst(2 * p, l, m, x, y, pred);
        if (res == -1) {
            res = findFirst(2 * p + 1, m, r, x, y, pred);
        }
        return res;
    }
    template<class F>   // 若要找 last，先右子樹遞迴即可
    int findFirst(int l, int r, F &&pred) {
        return findFirst(1, 0, n, l, r, pred);
    }
};
// ---define structure and info plus---
struct Info {
    ll sum;
    Info(ll sum_ = 0) : sum(sum_) {} 
};
Info operator + (const Info &a, const Info &b) {
    return { a.sum + b.sum };
}

void solve() {
    int n, q; cin >> n >> q;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Seg<Info> seg(a);

    struct Event {
        int id, op, x, y;
    };
    vector<pair<int, ll>> ans; // id, val

    vector<vector<Event>> events(1, vector<Event>());
    vector<vector<pair<int, int>>> ver_adj(1, vector<pair<int, int>>()); // v, 繼承的時間點
    int now_ver = 0;
    for (int i = 0; i < q; i++) {
        int op, k; cin >> op >> k;
        k--;
        if (op == 1) {
            int a, x;
            cin >> a >> x;
            a--;
            events[k].push_back({i, op, a, x});
        } else if (op == 2) {
            int a, b;
            cin >> a >> b;
            a--; b--;
            events[k].push_back({i, op, a, b});
        } else {
            now_ver++;
            ver_adj.push_back(vector<pair<int, int>>());
            events.push_back(vector<Event>());
            ver_adj[k].emplace_back(now_ver, i);
        }
    }

    for (auto &v : events) {
        sort(v.begin(), v.end(), [](const Event &a, const Event &b) {
            return a.id < b.id;
        });
    }

    auto dfs = [&](auto &&self, int u) -> void {
        vector<pair<int, ll>> record; // pos, val
        int i = 0, n = events[u].size();
        for (auto [v, id] : ver_adj[u]) {
            while (i < n && events[u][i].id < id) {
                auto &e = events[u][i];
                if (e.op == 1) {
                    record.emplace_back(e.x, seg.query(e.x, e.x + 1).sum);
                    seg.modify(e.x, Info(ll(e.y)));
                } else {
                    Info res = seg.query(e.x, e.y + 1);
                    ans.emplace_back(e.id, res.sum);
                }
                i++;
            }
            self(self, v);
        }
        while (i < n) {
            auto &e = events[u][i];
            if (e.op == 1) {
                record.emplace_back(e.x, seg.query(e.x, e.x + 1).sum);
                seg.modify(e.x, Info(ll(e.y)));
            } else {
                Info res = seg.query(e.x, e.y + 1);
                ans.emplace_back(e.id, res.sum);
            }
            i++;
        }
        reverse(record.begin(), record.end());
        for (auto [pos, val] : record) {
            seg.modify(pos, Info(val));
        }
    };
    dfs(dfs, 0);
    sort(ans.begin(), ans.end());
    for (auto [id, val] : ans) {
        cout << val << "\n";
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