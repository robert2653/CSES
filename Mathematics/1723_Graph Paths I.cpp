#include <bits/stdc++.h>
#define all(x) (x).begin(), (x).end()
#define pii pair<int, int> 
#define endl "\n"
#define int long long
using namespace std;
const int mod = 1e9 + 7;

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

void solve(){
    int n, m, k; cin >> n >> m >> k;
    vector g(n, vector<int>(n));
    for (int i = 0; i < m; i++) {
        int u, v; cin >> u >> v;
        u--; v--;
        g[u][v]++;
    }
    Mat mat(g);
    mat = mat ^ k;
    cout << mat.matrix[0][n - 1] << "\n";
}

signed main(){
    ios_base::sync_with_stdio(0);
    cin.tie(nullptr);
    int t = 1;
    // cin >> t;
    while (t--) {
        solve();
    }
}