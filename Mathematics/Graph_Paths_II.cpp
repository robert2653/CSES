#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll inf = 2E18;

template<class T>
struct Matrix {
    int n, m;
    vector<vector<T>> mat;
    constexpr Matrix(int n_, int m_) { init(n_, m_); }
    constexpr Matrix(vector<vector<T>> mat_) { init(mat_); }
    constexpr void init(int n_, int m_) {
        n = n_; m = m_;
        mat.assign(n, vector<T>(m));
    }
    constexpr void init(vector<vector<T>> &mat_) {
        n = mat_.size();
        m = mat_[0].size();
        mat = mat_;
    }
    constexpr Matrix &operator*=(const Matrix &rhs) & {
        assert(mat[0].size() == rhs.mat.size());
        int n = mat.size(), k = mat[0].size(), m = rhs.mat[0].size();
        Matrix res(vector<vector<ll>>(n, vector<ll>(m, inf)));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                for (int l = 0; l < k; l++) {
                    res.mat[i][j] = min(res.mat[i][j], mat[i][l] + rhs.mat[l][j]);
                }
            }
        }
        mat = res.mat;
        return *this;
    }
    friend constexpr Matrix operator*(Matrix lhs, const Matrix &rhs) {
        return lhs *= rhs;
    }
};
template<class T>
constexpr Matrix<T> unit(int n) {
    Matrix<T> res(n, n);
    for (int i = 0; i < n; i++) {
        res.mat[i][i] = 1;
    }
    return res;
}
template<class T>
constexpr Matrix<T> power(Matrix<T> a, ll b) {
    assert(a.n == a.m);
    // Matrix<T> res = unit<T>(a.n);
    Matrix<T> res = a; b -= 1;
    for (; b; b /= 2, a *= a)
        if (b % 2) res *= a;
    return res;
}

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector<vector<ll>> g(n, vector<ll>(n, inf));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u][v] = min<ll>(g[u][v], w);
    }
    Matrix<ll> mat(g);
    mat = power(mat, k);
    cout << (mat.mat[0][n - 1] == inf ? -1 : mat.mat[0][n - 1]) << "\n";
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