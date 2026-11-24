#include <bits/stdc++.h>
using namespace std;

using i8 = signed char;
using u8 = unsigned char;
using i32 = int;
using u32 = unsigned;
using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;
using u128 = unsigned __int128;

// clang-format off
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
template <typename T> void read(vector<T> &a) { for (auto &x : a) cin >> x; }
template <typename T> void show(const vector<T> &a, string_view sep = " ", string_view end = "\n") {
    for (auto i = 0; i < int(a.size()); ++i) {
        if (i) cout << sep;
        cout << a[i];
    }
    cout << end;
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

#ifndef SATURATING_HPP
#define SATURATING_HPP

#include <concepts>
#include <iostream>
#include <limits>

template <std::integral T> struct Saturating {
    T val;
    static constexpr T MAX = std::numeric_limits<T>::max();
    static constexpr T MIN = std::numeric_limits<T>::min();
    constexpr Saturating(T v = 0) : val(v) {}
    auto operator<=>(const Saturating &) const = default;
    constexpr Saturating &operator+=(Saturating other) {
        if (__builtin_add_overflow(val, other.val, &val)) {
            val = (val < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator-=(Saturating other) {
        if (__builtin_sub_overflow(val, other.val, &val)) {
            val = (val < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator*=(Saturating other) {
        auto sign = val ^ other.val;
        if (__builtin_mul_overflow(val, other.val, &val)) {
            val = (sign < 0) ? MIN : MAX;
        }
        return *this;
    }
    constexpr Saturating &operator/=(Saturating other) {
        if (val == MIN && other.val == -1) {
            val = MAX;
        } else {
            val /= other.val;
        }
        return *this;
    }
    friend constexpr Saturating operator+(Saturating a, Saturating b) {
        a += b;
        return a;
    }
    friend constexpr Saturating operator-(Saturating a, Saturating b) {
        a -= b;
        return a;
    }
    friend constexpr Saturating operator*(Saturating a, Saturating b) {
        a *= b;
        return a;
    }
    friend constexpr Saturating operator/(Saturating a, Saturating b) {
        a /= b;
        return a;
    }
    constexpr Saturating operator+() const { return *this; }
    constexpr Saturating operator-() const {
        if (val == MIN) {
            return {MAX};
        }
        return {-val};
    }
    constexpr Saturating abs() const {
        if (val == MIN) {
            return {MAX};
        }
        return (val < 0) ? Saturating(-val) : *this;
    }
    constexpr Saturating pow(unsigned long long exp) const {
        Saturating res = 1;
        Saturating base = *this;
        while (exp) {
            if (exp & 1) {
                res *= base;
            }
            base *= base;
            exp >>= 1;
        }
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, Saturating s) { return os << s.val; }
    friend std::istream &operator>>(std::istream &is, Saturating &s) { return is >> s.val; }
};

#endif // SATURATING_HPP

using S = Saturating<int>;

S op(S a, S b) { return int(min<i64>(S::MAX, lcm<i64>(a.val, b.val))); }

S e() { return 1; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<S> A(N);
    read(A);
    sparse_table<S, op, e> st(A);
    vector<int> X{0};
    for (auto i = 0; i < N; ++i) {
        auto p = i;
        while (p < N) {
            auto w = st.prod_idempotent(i, p + 1);
            X.push_back(w.val);
            auto pred = [&](int k) { return st.prod_idempotent(i, k + 1) == w; };
            p = *ranges::partition_point(views::iota(p, N), pred);
        }
    }
    ranges::sort(X);
    X.erase(unique(X.begin(), X.end()), X.end());
    for (auto i = 0; i < int(X.size()); ++i) {
        if (X[i] != i) {
            cout << i << "\n";
            return;
        }
    }
    cout << X.size() << "\n";
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
