#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<class T>
struct Mat {
    int m, n;
    constexpr static ll mod = 1e9 + 7;
    vector<vector<T>> matrix;
    Mat(int n_ = 0) { init(n_, n_); }
    Mat(int m_, int n_) { init(m_, n_); }
    Mat(vector<vector<T>> matrix_) { init(matrix_); }
    void init(int m_, int n_) {
        m = m_; n = n_;
        matrix.assign(m, vector<T>(n));
    }
    void init(vector<vector<T>> &matrix_) {
        m = matrix_.size();
        n = matrix_[0].size();
        matrix = matrix_;
    }
    vector<vector<T>> unit(int n) {   // 單位矩陣
        vector<vector<T>> res(n, vector<T>(n));
        for (int i = 0; i < n; i++) {
            res[i][i] = 1;
        }
        return res;
    }
    constexpr Mat &operator*=(const Mat& rhs) & {
        assert(matrix[0].size() == rhs.matrix.size());
        int m = matrix.size(), k = matrix[0].size(), n = rhs.matrix[0].size();
        Mat ans(m, n);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                for (int l = 0; l < k; l++) {
                    (ans.matrix[i][j] += (matrix[i][l] * rhs.matrix[l][j] % mod)) %= mod;
                }
            }
        }
        matrix = ans.matrix;
        return *this;
    }
    constexpr Mat &operator^=(ll p) & {
        assert(m == n); assert(p >= 0);
        Mat ans(p-- == 0 ? unit(m) : matrix);
        while (p > 0) {
            if (p & 1) ans *= *this;
            *this *= *this;
            p >>= 1;
        }
        matrix = ans.matrix;
        return *this;
    }
    friend Mat operator*(Mat lhs, const Mat &rhs) {
        lhs *= rhs;
        return lhs;
    }
    friend Mat operator^(Mat lhs, const ll p) {
        lhs ^= p;
        return lhs;
    }
};

int main() {
    ll n, ans; cin >> n;
    vector v(6, vector<ll>(6));
    vector<ll> init(12);
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
        Mat<ll> mat(v);
        Mat<ll> x(6);
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