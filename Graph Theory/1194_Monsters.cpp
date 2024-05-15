#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define lrep(i, st, n) for(int i = st; i < n; i++)
#define rep(i, st, n) for(int i = st; i <= n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define init(x, k) lrep(i, 0, sizeof(x)/sizeof(x[0])){x[i] = k;}
#define vec_init(x, k) lrep(i, 0, x.sz){x[i] = k;}
#define lc 2*now
#define rc 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef pair<ll, ll> pll;
typedef vector<ll> vl;
typedef vector<pll> vll;
typedef struct {
    int from; int to;
    ll weight;
} edge;
typedef struct {
    ll sum;
} Node;
const ll llinf = 1e18;
const int inf = 1e9;
const int MOD = 1e9+7;
const int maxn = 1e3+5;
// 有怪物能比你早到的點視為block
char graph[maxn][maxn];
int hito_go[maxn][maxn];
int Monsters_min[maxn][maxn];
int fx[4] = {0, 1, 0, -1};
int fy[4] = {1, 0, -1, 0};
int x, y, hx, hy, ex_x, ex_y;
char ans[maxn][maxn];
void print_ans(){
    deque<char> s;
    while(hx != ex_x || hy != ex_y){
        s.push_front(ans[ex_x][ex_y]);
        if(ans[ex_x][ex_y] == 'R') ex_y--;
        else if(ans[ex_x][ex_y] == 'L') ex_y++;
        else if(ans[ex_x][ex_y] == 'U') ex_x++;
        else if(ans[ex_x][ex_y] == 'D') ex_x--;
    }
    cout << s.size() << endl;
    for(auto i : s){
        cout << i;
    }
}
void mons_bfs(vector<pii> &monsters){
    vector<vector<bool>> vis(maxn, vector<bool>(maxn, 0));
    queue<pii> q;
    for(auto [x, y] : monsters){
        vis[x][y] = 1;
        Monsters_min[x][y] = 0;
        q.push({x, y}); 
    }
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        rep(i, 0, 3){
            int nx = x + fx[i], ny = y + fy[i];
            if(graph[nx][ny] == '.' && !vis[nx][ny]){
                q.push({nx, ny});
                Monsters_min[nx][ny] = Monsters_min[x][y] + 1;
                vis[nx][ny] = 1;
            }
        }
    }
}
void hito_bfs(){
    vector<vector<bool>> vis(maxn, vector<bool>(maxn, 0));
    queue<pii> q;
    vis[hx][hy] = 1;
    q.push({hx, hy});
    hito_go[hx][hy] = 0;
    while(!q.empty()){
        auto [x, y] = q.front(); q.pop();
        rep(i, 0, 3){
            int nx = x + fx[i], ny = y + fy[i];
            if(graph[nx][ny] == '.' && !vis[nx][ny]){
                q.push({nx, ny});
                hito_go[nx][ny] = hito_go[x][y] + 1;
                vis[nx][ny] = 1;
                if(hito_go[nx][ny] >= Monsters_min[nx][ny]) graph[nx][ny] = '#';
            }
        }
    }
}
bool find_exit_bfs(){
    vector<vector<bool>> vis(maxn, vector<bool>(maxn, 0));
    queue<pii> q;   q.push({hx, hy});   vis[hx][hy] = 1;
    while(!q.empty()){
        auto [nx, ny] = q.front(); q.pop();
        if(nx == 1 || nx == x || ny == 1 || ny == y){
            ex_x = nx, ex_y = ny; return 1;
        };
        if(graph[nx+1][ny] == '.' && !vis[nx+1][ny]){
            q.push({nx+1, ny});
            ans[nx+1][ny] = 'D';
            vis[nx+1][ny] = 1;
        }
        if(graph[nx-1][ny] == '.' && !vis[nx-1][ny]){
            q.push({nx-1, ny});
            ans[nx-1][ny] = 'U';
            vis[nx-1][ny] = 1;
        }
        if(graph[nx][ny+1] == '.' && !vis[nx][ny+1]){
            q.push({nx, ny+1});
            ans[nx][ny+1] = 'R';
            vis[nx][ny+1] = 1;
        }
        if(graph[nx][ny-1] == '.' && !vis[nx][ny-1]){
            q.push({nx, ny-1});
            ans[nx][ny-1] = 'L';
            vis[nx][ny-1] = 1;
        }
    }
    return 0;
}
void solve(){
    cin >> x >> y;
    vector<pii> monsters;
    rep(i, 1, x){
        rep(j, 1, y){
            cin >> graph[i][j];
            Monsters_min[i][j] = hito_go[i][j] = inf;
            if(graph[i][j] == 'M'){
                monsters.push_back({i, j});
                Monsters_min[i][j] = 0;
            }
            else if(graph[i][j] == 'A'){
                hx = i, hy = j;
            }
        }
    }
    // 圍起來
    rep(i, 0, x + 1){
        graph[i][y + 1] = graph[i][0] = '#';
    }
    rep(i, 0, y + 1){
        graph[0][i] = graph[x + 1][i] = '#';
    }
    mons_bfs(monsters);
    hito_bfs();
    if(find_exit_bfs()){
        cout << "YES\n";
        print_ans();
    }
    else cout << "NO\n";
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}