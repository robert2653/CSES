#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
int n; 
void print(int x){
    string s;
    while(x > 0){
        if(x&1){
            s.insert(s.begin(), '1');
        }
        else s.insert(s.begin(), '0');
        x >>= 1;
    }
    for(int i = 1, j = n-s.size(); i <= j; i++){
        s.insert(s.begin(), '0');
    }
    cout << s << endl;
}
void cur(int *now, int x, int sign){
    if(x < 0) return;
    cur(now, x-1, 1);
    *now += sign*pow(2, x);
    print(*now);
    cur(now, x-1, -1);
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    int now = 0; int *ptr = &now;
    print(0);
    cur(ptr, n-1, 1);
}