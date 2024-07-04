#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 碰到牆時，行進方向的左跟右都可走，就不對了

void solve() {
    const vector<int> dx{-1, 0, 1, 0};
    const vector<int> dy{0, 1, 0, -1};
    string s; cin >> s;
    const int n = sqrt(s.size() + 1);
    const int len = n * n - 1;

    int ans = 0;
    vector<int> road(n);
    vector vis(n + 2, vector<bool>(n + 2, false));

    string dir = "URDL";
    for (int i = 0; i < len; i++) {
        if (s[i] != '?') {
            road[i] = dir.find(s[i]);
        } else {
            road[i] = 4;
        }
    }

    for (int i = 0; i <= n + 1; i++) {
        vis[0][i] = vis[i][0] = vis[n + 1][i] = vis[i][n + 1] = true;
    }
    vis[1][1] = 1;

    auto dfs = [&](auto self, int x, int y, int step) {
        if (x == n && y == 1) {
            if (step == len) ans++;
            return;
        }
        if (road[step] != 4) {
            int nx = x + dx[road[step]];
            int ny = y + dy[road[step]];
            if (!vis[nx][ny]) {
                int opt = road[step];
                if (opt == 0 || opt == 2) {
                    if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx][ny + 1] && !vis[nx][ny - 1]) return;
                } else {
                    if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx + 1][ny] && !vis[nx - 1][ny]) return;
                }
                vis[nx][ny] = true;
                self(self, nx, ny, step + 1);
                vis[nx][ny] = false;
            }
        } else {
            for (int opt = 0; opt < 4; opt++) {
                int nx = x + dx[opt];
                int ny = y + dy[opt];
                if (vis[nx][ny]) continue;
                if (opt == 0 || opt == 2) {
                    if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx][ny + 1] && !vis[nx][ny - 1]) continue;
                } else {
                    if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx + 1][ny] && !vis[nx - 1][ny]) continue;
                }
                vis[nx][ny] = true;
                self(self, nx, ny, step + 1);
                vis[nx][ny] = false;
            }
        }
    };
    dfs(dfs, 1, 1, 0);
    cout << ans << "\n";
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


// AC Code
// 記住 vector 不利於大幅度遞迴

// #include <bits/stdc++.h>
 
// using namespace std;
// using ll = long long;
 
// // 碰到牆時，行進方向的左跟右都可走，就不對了
// const int dx[4] = {-1, 0, 1, 0};
// const int dy[4] = {0, 1, 0, -1};
// const int n = 7;
// const int len = 48;
// int ans = 0;
// int road[len];
// bool vis[n + 2][n + 2];
 
// int cnt = 0;
 
// void dfs(int x, int y, int step = 0) {
//     cnt++;
//     if (x == n && y == 1) {
//         if (step == len) ans++;
//         return;
//     }
//     if (road[step] != 4) {
//         int nx = x + dx[road[step]];
//         int ny = y + dy[road[step]];
//         if (!vis[nx][ny]) {
//             int opt = road[step];
//             if (opt == 0 || opt == 2) {
//                 if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx][ny + 1] && !vis[nx][ny - 1]) return;
//             } else {
//                 if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx + 1][ny] && !vis[nx - 1][ny]) return;
//             }
//             vis[nx][ny] = true;
//             dfs(nx, ny, step + 1);
//             vis[nx][ny] = false;
//         }
//     } else {
//         for (int opt = 0; opt < 4; opt++) {
//             int nx = x + dx[opt];
//             int ny = y + dy[opt];
//             if (vis[nx][ny]) continue;
//             if (opt == 0 || opt == 2) {
//                 if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx][ny + 1] && !vis[nx][ny - 1]) continue;
//             } else {
//                 if (vis[nx + dx[opt]][ny + dy[opt]] && !vis[nx + 1][ny] && !vis[nx - 1][ny]) continue;
//             }
//             vis[nx][ny] = true;
//             dfs(nx, ny, step + 1);
//             vis[nx][ny] = false;
//         }
//     }
// }
 
// void solve() {
//     string s;
//     cin >> s;
//     // n = sqrt(s.size() + 1);
//     // len = n * n - 1;
//     // road.resize(len);
 
//     string dir = "URDL";
//     for (int i = 0; i < len; i++) {
//         if (s[i] != '?') {
//             road[i] = dir.find(s[i]);
//         } else {
//             road[i] = 4;
//         }
//     }
//     // vis.assign(n + 2, vector<bool>(n + 2, false));
//     for (int i = 0; i <= n + 1; i++) {
//         vis[0][i] = vis[i][0] = vis[n + 1][i] = vis[i][n + 1] = true;
//     }
//     vis[1][1] = 1;
//     dfs(1, 1);
//     cout << ans << "\n";
// }
 
// int main() {
//     ios_base::sync_with_stdio(0);
//     cin.tie(nullptr);
//     int t = 1;
//     // cin >> t;
//     while (t--) {
//         solve();
//     }
// }