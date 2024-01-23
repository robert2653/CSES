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
// const int maxn = 2e5+5;
// 前特徵連結到後特徵
int n;
const int maxn = 1e5;
set<string> adj[maxn];
int string_to_int(string s){
    int ans = 0;
    int now = 1;
    while(!s.empty()){
        if(s.back() == '1'){
            ans += now;
        }
        now <<= 1;
        s.pop_back();
    }
    return ans;
}
void find_road(string now, vector<char> &ans){
    int u = string_to_int(now);
    while(adj[u].size()){
        string nxt = *adj[u].begin();
        adj[u].erase(nxt);
        find_road(nxt, ans);
    }
    ans.push_back(now[0]);
}
void generate_nums(string s){
    if(s.size() == n){
        adj[string_to_int(s.substr(0, n-1))].insert(s.substr(1, n-1));
        string a = s.substr(0, n-1), b = s.substr(1, n-1);
        return;
    }
    generate_nums(s + "1");
    generate_nums(s + "0");
}
void solve(){
    cin >> n;   string s;
    if(n == 1){
        cout << "10";
        return;
    }
    generate_nums(s);
    vector<char> ans;
    rep(i, 2, n) s.push_back('0');
    lrep(i, 2, n) ans.push_back('0');
    find_road(s, ans);
    for(auto i : ans){
        cout << i;
    }
}
int main(){
    IO;
    int t = 1;
    // cin >> t;
    while(t--){
        solve();
    }
}