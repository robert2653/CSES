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
const ll llinf = LLONG_MAX;
const int inf = INT_MAX;
const int maxn = 2e5+5;
// 前特徵連結到後特徵
int strbinary_to_int(string s){
    reverse(s.begin(), s.end());
    int ans = 0;
    while(s.size() > 0){
        ans <<= 1;
        if(s.back() == '1') ans++;
        s.pop_back();
    }
    return ans;
}
void find_road(int now, string &ans, vector<set<int>> &adj){
    while(adj[now].size()){
        int nxt = *adj[now].begin();
        adj[now].erase(nxt);
        find_road(nxt, ans, adj);
    }
    ans.push_back((now & 1) + '0');
}
void generate_nums(string s, int n, vector<set<int>> &adj){
    if(s.size() == n){
        adj[strbinary_to_int(s.substr(0, n - 1))].insert(strbinary_to_int(s.substr(1, n - 1)));
        // cerr << strbinary_to_int(s.substr(0, n - 1)) << " " << strbinary_to_int(s.substr(1, n - 1));
        return;
    }
    generate_nums(s + "0",  n, adj);
    generate_nums(s + "1", n, adj);
}
void solve(){
    int n;  cin >> n;
    vector<set<int>> adj(1 << n + 5);
    generate_nums("", n, adj);
    string ans;
    find_road(0, ans, adj);
    for(int i = 2; i < n; i++) ans.push_back('0');
    cout << ans;
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}