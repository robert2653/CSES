#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define all(x) (x).begin(), (x).end()
int main(){
    ll x;
    cin >> x;
    while(x!=1){
        cout << x << " ";
        if(x&1) x=(x*3)+1;
        else x/=2;
    }
    cout << 1;
}