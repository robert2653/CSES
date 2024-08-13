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
#define init(x) memset(x, 0, sizeof(x));
#define lp 2*now
#define rp 2*now+1
#define mid (L+R)/2
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = LLONG_MAX;
const int intf = INT_MAX;
const int maxn = 25+5;

int n, q;
ll nums[maxn] = {0};
ll prefix[maxn] = {0};
ll ans[maxn] = {0};
vii queries[maxn];
ll BIT[maxn] = {0};
ll contrib[maxn] = {0};
void update(int pos, ll val) {
	for (; pos <= n; pos += pos & -pos) BIT[pos] += val;
}
ll query(int a, int b) {
	ll ans = 0;
	for (; b; b -= b&-b) ans += BIT[b];
	for (a--; a; a -= a&-a) ans -= BIT[a];
	return ans;
}
void solve(){
    cin >> n >> q;
    rep(i, 1, n){
        cin >> nums[i];
        prefix[i] = prefix[i-1] + nums[i];
    }
    nums[n+1] = intf;
    prefix[n+1] = inf;
    rep(i, 1, q){
        int a, b; cin >> a >> b;
        queries[a].push_back({b, i});
    }
    deque<int> mono; mono.push_front(n+1);
    for(int i = n; i > 0; i--){ // 起點在n問到起點1
        while (nums[i] >= nums[mono.front()]) {
		    update(mono.front(), -contrib[mono.front()]);   // mono.front的contrib變成0
		    mono.pop_front();
	    }
	    contrib[i] = (mono.front() - 1 - i) * nums[i] - (prefix[mono.front() - 1] - prefix[i]);
	    update(i, contrib[i]);
	    mono.push_front(i);
        for (pii j : queries[i]) {  // pos 是值 <= Query r 的 mono index
			int pos = upper_bound(mono.begin(), mono.end(), j.first) - mono.begin() - 1;
			ans[j.second] = (pos ? query(i, mono[pos - 1]) : 0) +   // 到比y小的mono前都拉平
                            // mono到y數學解
			                (j.first - mono[pos]) * nums[mono[pos]] -
			                (prefix[j.first] - prefix[mono[pos]]);
		}
	}
    rep(i, 1, q){
        cout << ans[i] << endl;
    }
}
int main(){
    IO;
    solve();
}