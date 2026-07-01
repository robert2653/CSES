#include <bits/stdc++.h>
using namespace std;
using ll = long long;

constexpr ll inf = 2E18;

using Matrix = vector<vector<ll>>;
Matrix operator*(const Matrix &a, const Matrix &b) {
    int n = a.size(), k = a[0].size(), m = b[0].size();
    assert(k == b.size());
    Matrix res(n, vector<ll>(m, inf));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            for (int l = 0; l < k; l++)
                res[i][j] = min(res[i][j], a[i][l] + b[l][j]);
    return res;
}
Matrix power(Matrix a, ll b) {
    int n = a.size();
    Matrix res = a;
    b--;
    for (; b > 0; b >>= 1, a = a * a)
        if (b & 1) res = res * a;
    return res;
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<ll>> g(n, vector<ll>(n, inf));
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        u--; v--;
        g[u][v] = min<ll>(g[u][v], w);
    }
    Matrix mat(g);
    mat = power(mat, k);
    cout << (mat[0][n - 1] == inf ? -1 : mat[0][n - 1]) << "\n";

    return 0;
}