#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <int I = 0> void read(auto &a) { for (auto &x : a) { cin >> x; if constexpr (I) { x -= I; } } }
template <int I = 0> void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; if constexpr (I) { x += I; } cout << x; } cout << end;
}
// clang-format on

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

i64 op(i64 a, i64 b) { return std::gcd(a, b); }

i64 e() { return 0; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<i64> A(N);
    read(A);
    for (auto i = N - 2; 0 <= i; --i) {
        A[i + 1] -= A[i];
    }
    sparse_table<i64, op, e> st(A);
    auto ans = 0;
    for (auto i = 0; i < N; ++i) {
        auto pred = [&](int p) {
            auto l = i + 1, r = p + 1;
            auto g = st.prod(l, r);
            return g != 1;
        };
        auto it = ranges::partition_point(views::iota(i + 1, N), pred);
        ans = max(ans, *it - i);
    }
    cout << ans << "\n";
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
