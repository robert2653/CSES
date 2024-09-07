#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const double PI = acos(-1.0);
struct Complex {
    double x, y;
    Complex(double x_ = 0, double y_ = 0) : x(x_), y(y_) {}
    Complex operator+(const Complex &b) const {
        return Complex(x + b.x, y + b.y);
    }
    Complex operator-(const Complex &b) const {
        return Complex(x - b.x, y - b.y);
    }
    Complex operator*(const Complex &b) const {
        return Complex(x * b.x - y * b.y, x * b.y + y * b.x);
    }
};
vector<int> rev;
void fft(vector<Complex> &a, bool inv) {
    int n = a.size();
    if (int(rev.size()) != n) {
        int k = __builtin_ctz(n) - 1;
        rev.resize(n);
        for (int i = 0; i < n; i++) {
            rev[i] = rev[i >> 1] >> 1 | (i & 1) << k;
        }
    }
    for (int i = 0; i < n; i++) {
        if (rev[i] < i) {
            swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 1; k < n; k *= 2) {
        double ang = (inv ? -1 : 1) * PI / k;
        Complex wn(cos(ang), sin(ang));
        for (int i = 0; i < n; i += 2 * k) {
            Complex w(1);
            for (int j = 0; j < k; j++, w = w * wn) {
                Complex u = a[i + j];
                Complex v = a[i + j + k] * w;
                a[i + j] = u + v;
                a[i + j + k] = u - v;
            }
        }
    }
    if (inv) {
        for (auto &x : a) {
            x.x /= n;
            x.y /= n;
        }
    }
}
template<class T>
vector<T> mulT(const vector<T> &a, const vector<T> &b) {
    vector<Complex> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 2 << __lg(a.size() + b.size());
    fa.resize(n), fb.resize(n);
    fft(fa, false), fft(fb, false);
    for (int i = 0; i < n; i++) {
        fa[i] = fa[i] * fb[i];
    }
    fft(fa, true);
    vector<T> res(n);
    for (int i = 0; i < n; i++) {
        res[i] = round(fa[i].x);
    }
    return res;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;
    int n = s.length();
    vector<ll> a(n), b;
    for (int i = 0; i < n; i++) {
        if (s[i] == '1') {
            a[i] += 1;
        }
    }
    b = a;
    reverse(b.begin(), b.end());

    auto res = mulT(a, b);
    for (int i = n; i < 2 * n - 1; i++) {
        cout << res[i] << " \n"[i == 2 * n - 2];
    }

    return 0;
}