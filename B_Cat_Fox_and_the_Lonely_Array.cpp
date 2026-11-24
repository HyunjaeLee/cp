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
        assert(0 <= l && l <= r && r <= n_);
        auto sum = e();
        for (auto i = width_ - 1; 0 <= i; --i) {
            if ((1 << i) <= r - l) {
                sum = op(sum, table_[i][l]);
                l += (1 << i);
            }
        }
        return sum;
    }
    S prod_idempotent(int l, int r) {
        assert(0 <= l && l <= r && r <= n_);
        if (l == r) {
            return e();
        }
        auto i = std::bit_width(unsigned(r - l)) - 1;
        return op(table_[i][l], table_[i][r - (1 << i)]);
    }

private:
    int n_, width_;
    std::vector<std::vector<S>> table_;
};

#endif // SPARSE_TABLE_HPP

void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    copy_n(istream_iterator<int>(cin), N, begin(A));
    auto op = [](int a, int b) { return (a | b); };
    auto e = [] { return 0; };
    sparse_table<int, op, e> st(A);
    auto pred = [&](int k) {
        assert(1 <= k && k <= N);
        auto prod = st.prod_idempotent(0, k);
        for (auto i = 1; i + k <= N; ++i) {
            if (prod != st.prod_idempotent(i, i + k)) {
                return true;
            }
        }
        return false;
    };
    auto ans = *ranges::partition_point(views::iota(1, N + 1), pred);
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
