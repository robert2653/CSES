#include <bits/stdc++.h>
using namespace std;
string s; 
set<string> appear;
int sz;
void rec(string now, vector<bool> used){
    if(now.size() == sz){
        appear.insert(now);
    }
    else {
        for(int i = 0; i < sz; i++){
            if(!used[i]){
                used[i] = 1;
                now.push_back(s[i]);
                rec(now, used);
                used[i] = 0;
                now.pop_back();
            }
        }
    }
}
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    cin >> s;
    sz = s.size();
    vector<bool> used(sz, 0);
    string tmp;
    rec(tmp, used);
    cout << appear.size() << "\n";
    for(auto &i : appear) cout << i << "\n";
}