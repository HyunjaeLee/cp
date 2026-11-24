#include <bits/stdc++.h>
using namespace std;
using i64 = long long;
using i128 = __int128;

#ifndef SPARSE_TABLE_HPP
#define SPARSE_TABLE_HPP

#include <bit>
#include <cassert>
#include <type_traits>
#include <vector>

template <typename S, auto op, auto e> struct sparse_table {
    static_assert(std::is_invocable_r_v<S, decltype(op), S, S>, "op must be a function of type S(S, S)");
    static_assert(std::is_invocable_r_v<S, decltype(e)>, "e must be a function of type S()");
    sparse_table(const std::vector<S> &v)
        : n_((int)v.size()), width_(std::bit_width(v.size())), table_(width_, std::vector<S>(v.size())) {
        table_[0] = v;
        for (auto i = 1; i < width_; ++i) {
            for (auto j = 0; j + (1 << i) <= n_; ++j) {
                table_[i][j] = op(table_[i - 1][j], table_[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
    S prod(int l, int r) {
        if (0 <= l && l < r && r <= n_) {
            auto sum = e();
            for (auto i = width_ - 1; 0 <= i; --i) {
                if ((1 << i) <= r - l) {
                    sum = op(sum, table_[i][l]);
                    l += (1 << i);
                }
            }
            return sum;
        } else {
            return e();
        }
    }
    S prod_idempotent(int l, int r) {
        if (0 <= l && l < r && r <= n_) {
            auto i = std::bit_width(unsigned(r - l)) - 1;
            return op(table_[i][l], table_[i][r - (1 << i)]);
        } else {
            return e();
        }
    }

private:
    int n_, width_;
    std::vector<std::vector<S>> table_;
};

#endif // SPARSE_TABLE_HPP

void solve() {
    auto op = [](int a, int b) { return a + b; };
    auto e = [] { return 0; };
    int n, k, x;
    cin >> n >> k >> x;
    vector<int> a(n);
    for (auto i = 0; i < n; ++i) {
        cin >> a[i];
    }
    ranges::sort(a | views::reverse);
    sparse_table<int, op, e> sp(a);
    auto ans = numeric_limits<int>::min();
    for (auto l = 0; l <= k; ++l) {
        auto val = -sp.prod(l, min(n, l + x)) + sp.prod(l + x, n);
        ans = max(ans, val);
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
