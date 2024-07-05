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

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector g(n, vector<ll>(n));
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u][v]++;
    }
    Mat<ll> mat(g);
    mat = mat ^ k;
    cout << mat.matrix[0][n - 1] << "\n";
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}