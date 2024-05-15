#include <bits/stdc++.h>
using namespace std;
int main(){
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    string s; cin >> s;
    int size = s.size();
    map<char, int> mp;
    for(auto &i : s) mp[i]++;
    vector<char> ans;
    if(size & 1){
        int cnt = 0; char c;
        for(auto i : mp){
            if(i.second & 1){
                cnt++; c = i.first;
                i.second = (i.second - 1) / 2;
                while(i.second--) ans.push_back(i.first);
            }
            else {
                i.second /= 2;
                while(i.second--) ans.push_back(i.first);
            }
            if(cnt == 2){
                cout << "NO SOLUTION"; return 0;
            }
        }
        for(auto it = ans.begin(); it != ans.end(); it++) cout << *it;
        cout << c;
        for(auto it = ans.rbegin(); it != ans.rend(); it++) cout << *it;
    }
    else {
        for(auto i : mp){
            if(i.second & 1){
                cout << "NO SOLUTION"; return 0;
            }
            else {
                i.second /= 2;
                while(i.second--) ans.push_back(i.first);
            }
        }
        for(auto it = ans.begin(); it != ans.end(); it++) cout << *it;
        for(auto it = ans.rbegin(); it != ans.rend(); it++) cout << *it;
    }
}