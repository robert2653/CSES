#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct Line {
    ll m = 0, b = 0;
    ll eval(ll x) {
        return m * x + b;
    }
};
struct CHT { // 用在查詢單調斜率也單調
    int n, lptr, rptr; vector<Line> hull;
    CHT(int n_ = 0, Line init_ = Line()) {
        init(n_, init_);
    }
    void init(int n_ = 0, Line init_ = Line()) {
        n = n_; hull.resize(n); reset(init_); 
    }
    void reset(Line init_ = Line()) {
        lptr = rptr = 0; hull[0] = init_;
    }
    bool pop_front(Line &l1, Line &l2, ll x) {
        // 斜率遞減、查詢遞增，因此只要左直線的 Y >= 右直線的 Y
        // 代表查詢的當下，右線段的高度已經低於左線段了
        return l1.eval(x) >= l2.eval(x);
    }
    bool pop_back(Line &l1, Line &l2, Line &l3) {
        // 本題斜率遞減、上凸包
        // 因此只要 l2 跟 l3 的 X 交點 <= l1 跟 l3 的 X 交點，l2 就用不到了
        return (l3.b - l2.b) * (l1.m - l3.m) <= (l3.b - l1.b) * (l2.m - l3.m);
    }
    void insert(Line L) {
        while (rptr - lptr > 0 && pop_back(hull[rptr - 1], hull[rptr], L))
            rptr--;
        hull[++rptr] = L;
    }
    ll query(ll x) {
        while (rptr - lptr > 0 && pop_front(hull[lptr], hull[lptr + 1], x))
            lptr++;
        return hull[lptr].eval(x);
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int n, K;
    cin >> n >> K;
    
    vector<ll> pre(n + 1, 0);
    for (int i = 1; i <= n; i++) {
        cin >> pre[i];
        pre[i] += pre[i - 1];
    }
    
    vector<ll> dp(n + 1);
    
    for (int i = 1; i <= n; i++) {
        dp[i] = pre[i] * pre[i];
    }
    
    CHT cht(n + 1);
    // dp[i] - s[i]^2 = (-2s[j]) * s[i] + s[j]^2
    // 斜率遞減查詢遞增
    for (int k = 1; k <= K - 1; k++) { // 切 k 次
        cht.reset();
        for (int i = 1; i <= k; i++) {
            cht.insert({-2LL * pre[i], dp[i] + pre[i] * pre[i]});
        }
        for (int i = k + 1; i <= n; i++) {
            auto val = cht.query(pre[i]);
            cht.insert({-2LL * pre[i], dp[i] + pre[i] * pre[i]});
            dp[i] = pre[i] * pre[i] + val;
        }
    }
    
    cout << dp[n] << "\n";
    
    return 0;
}