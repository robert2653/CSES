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
char lab[maxn][maxn], ans[maxn][maxn];
bool vis[maxn][maxn];
int x, y, ax, ay, bx, by;

int fx[4] = {0, 1, 0, -1};
int fy[4] = {1, 0, -1, 0};
void print_ans(){
    deque<char> s;
    while(ax != bx || ay != by){
        s.push_front(ans[bx][by]);
        if(ans[bx][by] == 'R') by--;
        else if(ans[bx][by] == 'L') by++;
        else if(ans[bx][by] == 'U') bx++;
        else if(ans[bx][by] == 'D') bx--;
    }
    cout << s.size() << endl;
    for(auto i : s){
        cout << i;
    }
}
bool bfs(){
    queue<pii> q;   q.push({ax, ay});   vis[ax][ay] = 1;
    while(!q.empty()){
        auto [nx, ny] = q.front(); q.pop();
        if(nx == bx && ny == by) return 1;
        if(lab[nx+1][ny] == '.' && !vis[nx+1][ny]){
            q.push({nx+1, ny});
            ans[nx+1][ny] = 'D';
            vis[nx+1][ny] = 1;
        }
        if(lab[nx-1][ny] == '.' && !vis[nx-1][ny]){
            q.push({nx-1, ny});
            ans[nx-1][ny] = 'U';
            vis[nx-1][ny] = 1;
        }
        if(lab[nx][ny+1] == '.' && !vis[nx][ny+1]){
            q.push({nx, ny+1});
            ans[nx][ny+1] = 'R';
            vis[nx][ny+1] = 1;
        }
        if(lab[nx][ny-1] == '.' && !vis[nx][ny-1]){
            q.push({nx, ny-1});
            ans[nx][ny-1] = 'L';
            vis[nx][ny-1] = 1;
        }
    }
    return 0;
}
void solve(){
    cin >> x >> y;
    rep(i, 1, x){
        rep(j, 1, y){
            cin >> lab[i][j];
            if(lab[i][j] == 'A'){
                ax = i, ay = j;
                // lab[i][j] = '.';
            }
            if(lab[i][j] == 'B'){
                bx = i, by = j;
                lab[i][j] = '.';
            }
        }
    }
    // 圍起來
    rep(i, 0, x + 1){
        lab[i][y + 1] = lab[i][0] = '#';
    }
    rep(i, 0, y + 1){
        lab[0][i] = lab[x + 1][i] = '#';
    }
    if(bfs()){
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