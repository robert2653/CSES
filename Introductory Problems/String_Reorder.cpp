#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();
    priority_queue<pair<char, int>, vector<pair<char, int>>, greater<pair<char, int>>> pq;
    vector<int> cnt(26, 0);
    for (int i = 0; i < n; i++) {
        cnt[s[i] - 'A']++;
    }
    for (int i = 0; i < 26; i++) {
        if (cnt[i] > 0) {
            pq.emplace(char(i + 'A'), cnt[i]);
        }
    }
    string ans;
    if (*max_element(cnt.begin(), cnt.end()) > (n + 1) / 2) {
        cout << "-1\n";
        return 0;
    }
    while (!pq.empty()) {
        if (*max_element(cnt.begin(), cnt.end()) == (n + 1) / 2 && n % 2 == 1) {
            break;
        }
        auto [c, freq] = pq.top();
        pq.pop();
        if (ans.empty() || ans.back() != c) {
            ans.push_back(c);
            freq--;
            cnt[c - 'A']--;
            if (freq > 0) {
                pq.emplace(c, freq);
            }
        } else {
            auto [c2, freq2] = pq.top();
            pq.pop();
            pq.emplace(c, freq);
            ans.push_back(c2);
            freq2--;
            cnt[c2 - 'A']--;
            if (freq2 > 0) {
                pq.emplace(c2, freq2);
            }
        }
        n--;
    }
    char mxc = max_element(cnt.begin(), cnt.end()) - cnt.begin() + 'A';
    for (int i = 0, turn = 0; i < 26; i++) {
        if (i == mxc - 'A') continue;
        while (cnt[i] > 0) {
            if (turn == 0) {
                ans.push_back(mxc);
            } else {
                ans.push_back(char(i + 'A'));
                cnt[i]--;
            }
            turn ^= 1;
        }
    }
    ans.push_back(mxc);
    cout << ans << "\n";
    return 0;
}