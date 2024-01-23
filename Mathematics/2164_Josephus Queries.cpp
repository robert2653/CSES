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
#define init = {0}
typedef long long int ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;
typedef struct{
    int from; int to;
    ll weight;
} edge;
const ll inf = 1LL << 62;
map<int, int> used;
int q;
int solve(int a, int b){
    if (a == 1) return 1;
    if (b <= (a + 1) / 2){
        if (2 * b > a)
            return 1;   // 總數奇數的第一位，b == (a + 1) / 2
        return 2 * b;
    }
    int tmp = solve(a >> 1, b - (a + 1) / 2);   // a >> 1 代表拿走(a + 1) / 2 個
    if (a & 1) return 2 * tmp + 1;
    // 有拿走第一個，回傳要再 * 2 再 + 1
    // ex: 傳入1～7，拿走2、4、6、1，回傳1、2、3，實際上是3、5、7
    return 2 * tmp - 1;
    // 沒拿走第一個，做成連奇數即可
    // ex: 傳入1～6，拿走2、4、6，回傳1、2、3，實際上是1、3、5
}
int main(){
    IO;
    cin >> q;
    rep(i, 0, q){
        int a, b; cin >> a >> b;
        cout << solve(a, b) << endl;
    }
}