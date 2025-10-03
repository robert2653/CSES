#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const double PI = acos(-1.0);
using cd = complex<double>;
vector<int> rev;
void fft(vector<cd> &a, bool inv) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++)
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
    }
    for (int i = 0; i < n; i++)
        if (rev[i] < i)
            swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2) {
        double ang = (inv ? -1 : 1) * PI / k;
        cd wn(cos(ang), sin(ang));
        for (int i = 0; i < n; i += 2 * k) {
            cd w(1);
            for (int j = 0; j < k; j++, w = w * wn) {
                cd u = a[i + j];
                cd v = a[i + j + k] * w;
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
    if (inv) for (auto &x : a) x /= n;
}
template<class T>
vector<double> mulT(const vector<T> &a, const vector<T> &b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1, tot = a.size() + b.size() - 1;
    while (n < tot) n *= 2;
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++)
        fa[i] = fa[i] * fb[i];
    fft(fa, true);
    vector<double> res(tot);
    for (int i = 0; i < tot; i++)
        res[i] = fa[i].real();
    return res; // use llround if need
}

int main() {
    int k, n, m;
    cin >> k >> n >> m;

    vector<int> a(k + 1), b(k + 1);
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        a[x] += 1;
    }
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        b[x] += 1;
    }
    auto res = mulT(a, b);
    for (int w = 2; w <= 2 * k; ++w) {
        cout << llround(res[w]) << " ";
    }

    return 0;
}
