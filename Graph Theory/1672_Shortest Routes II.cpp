#include <bits/stdc++.h>
using namespace std;
using ll = long long int;
const int maxn = 505;
ll graph[maxn][maxn];
ll dis[maxn][maxn];
ll n, m, q; ll a, b, c;
const ll INF = 1e18;
int main(){
    cin >> n >> m >> q;
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            graph[i][j] = INF;
        }   
    }
    for(int i = 0; i < m; i++){
        cin >> a >> b >> c;
        graph[a][b] = min(graph[a][b], c);
        graph[b][a] = min(graph[b][a], c);
    }
    for(int i = 0; i <= n; i++) {
        for(int j = 0; j <= n; j++) {
            dis[i][j] = graph[i][j];
        }   
    }
    for(int i = 0; i <= n; i++)
        dis[i][i] = 0;
 
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            for(int j = 1; j <= n; j++){
                dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
            }
        }
    }
    for(int i = 0; i < q; i++){
        cin >> a >> b;
        cout << (dis[a][b] >= INF ? -1 : dis[a][b]) << "\n";
    }
}