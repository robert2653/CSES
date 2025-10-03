#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    iota(v.begin(), v.end(), 0);
    auto ask = [](int l, int r) -> bool {
        cout << "? " << l + 1 << " " << r + 1 << endl;
        string res;
        cin >> res;
        return res == "YES";
    };
    auto partition = [&](int l, int r) {
        int pivot = v[l + rand() % (r - l - 1)];
        int i = l, j = r;
        while (true) {
            while (ask(i, pivot)) i++;
            while (ask(pivot, i)) j--;
            if (i >= j) return j;
            swap(v[i], v[j]);
        }
    };
    auto quickSort = [&](auto self, int l, int r) {
        if (l == r) {
            return;
        }
        int pivot = partition(l, r);
        self(self, l, pivot);
        self(self, pivot + 1, r);
    };
    quickSort(quickSort, 0, n - 1);
    vector<int> ans(n);
    for (int i = 0; i < n; i++) {
        ans[i] = v[i];
    }
    return 0;
}