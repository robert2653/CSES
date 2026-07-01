#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 預先分配足夠大的空間
int h[3005];
int stk[3005]; 

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<string> g(n);
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }

    vector<ll> total_ans(k, 0); // 用 vector 存 K 個答案

    for (int c = 0; c < k; c++) {
        char target = 'A' + c;
        // h 陣列在 K 迴圈外層初始化一次即可
        memset(h, 0, sizeof(h)); 

        for (int i = 0; i < n; i++) { // 枚舉底列 i
            ll cur = 0;
            int top = 0; // 棧頂指標
            stk[0] = -1; // 放入哨兵 (sentinel)

            // 更新 h 並同時計算
            for (int j = 0; j < n; j++) {
                // 1. 更新 h[j]
                if (g[i][j] == target) {
                    h[j]++;
                } else {
                    h[j] = 0;
                }

                // 2. 計算直方圖 (與你的邏輯相同)
                while (top > 0 && h[stk[top]] >= h[j]) {
                    int id = stk[top--];
                    cur -= 1LL * h[id] * (id - stk[top]);
                }
                cur += 1LL * h[j] * (j - stk[top]);
                stk[++top] = j;
                total_ans[c] += cur;
            }
        }
    }

    for (int c = 0; c < k; c++) {
        cout << total_ans[c] << "\n";
    }
    return 0;
}