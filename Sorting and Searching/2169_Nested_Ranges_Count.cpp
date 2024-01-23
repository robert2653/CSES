#include <bits/stdc++.h>
using namespace std;
#define all(x) (x).begin(), (x).end()
typedef long long int ll;
typedef pair<int, int> pii;
typedef struct {
    ll u, v, id;
} line;
bool cmp1(line a, line b){
    if(a.u == b.u) return a.v < b.v;
    else return a.u > b.u;
}
bool cmp2(line a, line b){
    if(a.u == b.u) return a.v > b.v;
    else return a.u < b.u;
}
void update(vector<ll> &BIT, int a, int n){
    for(; a <= n; a += (a&-a)){
        BIT[a]++;
    }
}
ll query(vector<ll> &BIT, int a, int b){
    ll ans = 0;
    for(; b; b -= (b&-b)){
        ans += BIT[b];
    }
    for(--a; a; a -= (a&-a)){
        ans -= BIT[a];
    }
    return ans;
}
int main(){
    int n; cin >> n;
    vector<ll> contain(n + 1), contained(n + 1);
    vector<line> lines(n);
    vector<ll> concrete(n);
    vector<ll> BIT1(n + 1, 0), BIT2(n + 1, 0);
    for(int i = 0; i < n; i++){
        cin >> lines[i].u >> lines[i].v;
        concrete[i] = lines[i].v;
        lines[i].id = i;
    }
    sort(all(concrete));
    for(int i = 0; i < n; i++){
        lines[i].v = lower_bound(concrete.begin(), concrete.end(), lines[i].v) - concrete.begin() + 1;
    }
    sort(all(lines), cmp1);
    for(int i = 0; i < n; i++){
        contain[lines[i].id] = query(BIT1, 1, lines[i].v);
        update(BIT1, lines[i].v, n);
    }
    sort(all(lines), cmp2);
    for(int i = 0; i < n; i++){
        contained[lines[i].id] = query(BIT2, lines[i].v, n);
        update(BIT2, lines[i].v, n);
    }
    for(int i = 0; i < n; i++){
        cout << contain[i] << " ";
    }
    cout << "\n";
    for(int i = 0; i < n; i++){
        cout << contained[i] << " ";
    }
}