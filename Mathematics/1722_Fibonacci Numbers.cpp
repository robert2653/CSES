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
    void mul(Mat b) {
        Mat ans(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                for (int k = 0; k < n; k++) {
                    (ans.matrix[i][j] += (matrix[i][k] * b.matrix[k][j] % mod)) %= mod;
                }
            }
        }
        matrix = ans.matrix;
    }
    void pow(int p) {
        Mat x = *this;
        *this = unit(n);
        while (p > 0) {
            if (p & 1) {
                mul(x);
            }
            x.mul(x);
            p >>= 1;
        }
    }
};
signed main() {
    int n, ans; cin >> n;
    if (n <= 2) {
        vector<int> v = {0, 1, 1};
        ans = v[n];
    }
    else {
        Mat mat({{1, 1}, {1, 0}});
        Mat x(2);
        x.matrix = {{1, 1}, {1, 0}};
        x.pow(n - 2);
        mat.mul(x);
        ans = mat.matrix[0][0];
    }
    cout << ans << "\n";
}
// 初始矩陣  轉移式
// f2 f1    1 1     f3 f2
// f1 f0    1 0  => f2 f1