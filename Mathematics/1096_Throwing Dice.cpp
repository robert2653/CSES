#include <bits/stdc++.h>
using namespace std;
const int mod = 1e9 + 7;
#define int long long
struct Mat {
    int n;
    vector<vector<int>> matrix;
    Mat(int n) {
        this->n = n;
        matrix.resize(n);
        for (int i = 0; i < n; i++) {
            matrix[i].resize(n);
        }
    }
    Mat(vector<vector<int>> matrix) {
        this->n = matrix.size();
        this->matrix = matrix;
    }
    Mat unit(int n) {   // 單位矩陣
        Mat res(n);
        for (int i = 0; i < n; i++) {
            res.matrix[i][i] = 1;
        }
        return res;
    }
    Mat operator * (Mat b) {
        Mat ans(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans.matrix[i][j] += (matrix[i][k] * b.matrix[k][j] % mod)) %= mod;
                }
            }
        }
        return ans;
    }
    Mat operator *= (Mat b) { *this = *this * b; return *this; }
    Mat operator ^ (int p) {
        Mat x = *this;
        Mat ans = unit(n);
        while (p > 0) {
            if (p & 1) {
                ans *= x;
            }
            x *= x;
            p >>= 1;
        }
        return ans;
    }
    Mat operator ^= (int p) { *this = *this ^ p; return *this; }
};
signed main() {
    int n, ans; cin >> n;
    vector v(6, vector<int>(6));
    vector<int> init(12);
    init[0] = 1;
    for (int i = 1; i <= 11; i++) {
        for (int d = -6; d <= -1; d++) {
            if (i + d >= 0)
                init[i] += init[i + d];
        }
    }
    for (int i = 0, now = 11; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            v[i][j] = init[now];
            now--;
        }
        now += 5;
    }
    if (n <= 11) {
        ans = init[n];
    }
    else {
        Mat mat(v);
        Mat x(6);
        for (int i = 0; i < 6; i++) x.matrix[i][0] = 1;
        for (int i = 0, now = 1; i < 5; i++) {
            x.matrix[i][now] = 1;
            now++;
        }
        x ^= n - 11;
        mat *= x;
        ans = mat.matrix[0][0];
    }
    cout << ans << "\n";
}
// 初始矩陣  轉移式
// f11 f10 f9 f8 f7 f6 1 1 0 0 0 0 
// f10 f9 f8 f7 f6 f5  1 0 1 0 0 0
// f9 f8 f7 f6 f5 f4   1 0 0 1 0 0
// f8 f7 f6 f5 f4 f3   1 0 0 0 1 0
// f7 f6 f5 f4 f3 f2   1 0 0 0 0 1
// f6 f5 f4 f3 f2 f1   1 0 0 0 0 0

// f12 f11 f10 f9 f8 f7
// f11 f10 f9 f8 f7 f6
// f10 f9 f8 f7 f6 f5
// f9 f8 f7 f6 f5 f4
// f8 f7 f6 f5 f4 f3
// f7 f6 f5 f4 f3 f2