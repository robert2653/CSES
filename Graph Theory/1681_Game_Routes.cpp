// #include <bits/stdc++.h> //使用拓樸+dp
// using namespace std;
// typedef long long int ll;
// #define all(x) (x).begin(), (x).end()
// vector<int> graph[100005];
// vector<int> inv_graph[100005];
// vector<ll> dp(100005, 0);
// vector<ll> in(100005, 0);
// const int mod = 1e9+7;
// int n, m;
// ll ans = 0;
// int main(){
//     ios_base::sync_with_stdio(0);
//     cin.tie();
//     cin >> n >> m;
//     for(int i = 0; i < m; i++){
//         int a, b; cin >> a >> b;
//         graph[a].push_back(b);
//         inv_graph[b].push_back(a);
//         in[b]++;
//     }
//     dp[1] = 1;
//     queue<int> q;
    
//     // q.push(1);
//     for (int i = 0; i < n; i++) {
// 		if (in[i] == 0){
//             q.push(i);
//             // cout << "push " << i << endl;
//         }
// 	}

//     while(!q.empty()){
//         int tmp = q.front(); q.pop();
//         for(auto nxt : graph[tmp]){ // 不會再走到了，丟進去queue
//             in[nxt]--;
//             if(in[nxt] == 0){
//                 q.push(nxt);
//             }
//         }
//         for(auto lst : inv_graph[tmp]){ // 往前找，累加
//             dp[tmp] = (dp[tmp]+dp[lst]) % mod;
//         }
//     }
//     // for(int i = 1; i <= n; i++) cout << dp[i];
//     cout << dp[n];
// }
#include <bits/stdc++.h> //使用拓樸+dp
using namespace std;
typedef long long int ll;
#define all(x) (x).begin(), (x).end()
vector<int> graph[100005];
vector<int> inv_graph[100005];
vector<ll> dp(100005, 0);
vector<ll> in(100005, 0);
const int mod = 1e9+7;
int n, m;
ll ans = 0;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie();
    cin >> n >> m;
    for(int i = 0; i < m; i++){
        int a, b; cin >> a >> b;
        graph[a].push_back(b);
        in[b]++;
    }
    dp[1] = 1;
    queue<int> q;
    
    for (int i = 1; i <= n; i++) {
		if (in[i] == 0){
            q.push(i);
        }
	}
    while(!q.empty()){
        int now = q.front(); q.pop();
        ans = max(ans, dp[now]);
        for(auto v : graph[now]){
            in[v]--;
            dp[v] = (dp[v] + dp[now]) % mod;
            if(in[v] == 0){
                q.push(v);
            }
        }
    }
    // for(int i = 1; i <= n; i++) cout << dp[i];
    cout << dp[n];
}