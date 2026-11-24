#include <bits/stdc++.h>
using namespace std;
using u32 = unsigned int;

// op is an idempotent function
template <typename S, auto op> struct sparse_table {
    sparse_table(const vector<S> &a) : n((int)a.size()), w(bit_width(a.size())), data(w, vector<S>(n)) {
        data[0] = a;
        for (auto i = 1; i < w; ++i)
            for (auto j = 0; j + (1 << i) <= n; ++j)
                data[i][j] = op(data[i - 1][j], data[i - 1][j + (1 << (i - 1))]);
    }
    S prod(int l, int r) { // [l, r) O(1)
        assert(0 <= l && l < r && r <= n);
        auto i = bit_width(unsigned(r - l)) - 1;
        return op(data[i][l], data[i][r - (1 << i)]);
    }
    int n, w;
    vector<vector<S>> data;
};

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &x : A) {
        cin >> x;
    }
    auto op = [](auto a, auto b) { return min(a, b); };
    sparse_table<int, op> S(A);
    while (Q--) {
        int l, r;
        cin >> l >> r;
        auto ans = S.prod(l, r);
        cout << ans << '\n';
    }
}
