// 線段樹
// 左(s < t): dis = (pizza[s] - s) + t;
// 右(t < s): dis = (pizza[s] + s) - t;
//          8  6  4  5  7  5
//   left:  7  4  1  1  2  -1
//  right:  9  8  7  9  12 11
//                          1:1~6
//           2:1~3                          3:4~6
//   4:1~2           5:3            6:4~5           7:6
// 8:1    9:2    10:x    11:x    12:4    13:5   14:x    15:x
#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
#define endl "\n"
#define rep(i, st, n) for(int i = st; i < n; i++)
#define sz size()
#define pb(x) push_back(x)
#define ppb pop_back()
#define pp pop()
#define tp top()
#define ph(x) push(x)
#define IO ios_base::sync_with_stdio(0); cin.tie(0);
#define left_child 2*now
#define right_child 2*now+1
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{ 
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;
const int maxn = 2e5+5;

vector<int> min_left(4*maxn, INT_MAX);
vector<int> min_right(4*maxn, INT_MAX);
int pizza[maxn];
int n, q;
void build(int L, int R, int now){
    if(L == R){
        min_left[now] = pizza[L]-L;
        min_right[now] = pizza[L]+L;
        return;
    }
    int M = (L + R) / 2;
    build(L, M, left_child);
    build(M + 1, R, right_child);
    min_left[now] = min(min_left[left_child], min_left[right_child]);
    min_right[now] = min(min_right[left_child], min_right[right_child]);
}
int left_query(int l, int r, int L, int R, int now){
    if(l <= L && R <= r)
        return min_left[now];
    int M = (L + R) / 2;
    if(r <= M)
        return left_query(l, r, L, M, left_child);
    else if(l > M) 
        return left_query(l, r, M + 1, R, right_child);
    else 
        return min(left_query(l, r, L, M, left_child), 
                   left_query(l, r, M + 1, R, right_child));
}
int right_query(int l, int r, int L, int R, int now){
    if(l <= L && R <= r)
        return min_right[now];
    int M = (L + R) / 2;
    if(r <= M) 
        return right_query(l, r, L, M, left_child);
    else if(l > M) 
        return right_query(l, r, M + 1, R, right_child);
    else
        return min(right_query(l, r, L, M, left_child), right_query(l, r, M + 1, R, right_child));
}
void modify(int p, int x, int L, int R, int now){
    if(L == R){
        min_left[now] = x-L;
        min_right[now] = x+L;
        return;
    }
    int M = (L + R) / 2;
    if(p <= M)
        modify(p, x, L, M, left_child);
    else 
        modify(p, x, M + 1, R, right_child);
    min_left[now] = min(min_left[left_child], min_left[right_child]);
    min_right[now] = min(min_right[left_child], min_right[right_child]);
}
int main(){
    IO;
    cin >> n >> q;
    rep(i, 1, n+1){
        int p; cin >> p;
        pizza[i] = p;
    }
    build(1, n, 1);
    // rep(i, 1, 4*n+1) cout << i << " : " << min_left[i] << endl;
    // rep(i, 1, 4*n+1) cout << i << " : " << min_right[i] << endl;
    rep(i, 0, q){
        int op; cin >> op;
        if(op == 1){
            int p, x; cin >> p >> x;
            modify(p, x, 1, n, 1);
        }
        else {
            int p; cin >> p;
            int ans = min(left_query(1, p, 1, n, 1) + p, right_query(p, n, 1, n, 1) - p);
            cout << ans << endl;
        }
    }
}