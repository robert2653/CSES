#include <bits/stdc++.h>
using namespace std;
int n; 
void rec(int a, int b, int c, int step){
    if(step == n) return;
    rec(a, c, b, step + 1);
    cout << a << " " << c << "\n";
    rec(b, a, c, step + 1);
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);cin >> n;
    cout << pow(2, n) - 1 << "\n";
    rec(1, 2, 3, 0);
}