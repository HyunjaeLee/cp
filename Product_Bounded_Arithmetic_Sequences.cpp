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

#ifndef SATURATING_HPP
#define SATURATING_HPP

#include <concepts>
#include <iostream>
#include <limits>

template <std::integral T> struct Saturating {
    static constexpr T MAX = std::numeric_limits<T>::max();
    static constexpr T MIN = std::numeric_limits<T>::min();
    constexpr Saturating(T v = 0) : val_(v) {}
    auto operator<=>(const Saturating &) const = default;
    constexpr Saturating &operator+=(Saturating other) {
        if (__builtin_add_overflow(val_, other.val_, &val_)) {
            val_ = (val_ < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator-=(Saturating other) {
        if (__builtin_sub_overflow(val_, other.val_, &val_)) {
            val_ = (val_ < 0) ? MAX : MIN;
        }
        return *this;
    }
    constexpr Saturating &operator*=(Saturating other) {
        auto sign = val_ ^ other.val_;
        if (__builtin_mul_overflow(val_, other.val_, &val_)) {
            val_ = (sign < 0) ? MIN : MAX;
        }
        return *this;
    }
    constexpr Saturating &operator/=(Saturating other) {
        if (val_ == MIN && other.val_ == -1) {
            val_ = MAX;
        } else {
            val_ /= other.val_;
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
        if (val_ == MIN) {
            return {MAX};
        }
        return {-val_};
    }
    constexpr Saturating abs() const {
        if (val_ == MIN) {
            return {MAX};
        }
        return (val_ < 0) ? Saturating(-val_) : *this;
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
    constexpr T val() const { return val_; }
    friend std::ostream &operator<<(std::ostream &os, Saturating s) { return os << s.val_; }
    friend std::istream &operator>>(std::istream &is, Saturating &s) { return is >> s.val_; }

private:
    T val_;
};

#endif // SATURATING_HPP

void solve() {
    i64 N;
    cin >> N;
    using S = Saturating<i64>;
    i64 ans = 0;
    for (i64 a = 1; a <= 1'000'000; ++a) {
        for (i64 len = 3; len < 20; ++len) {
            auto pred = [&](i64 d) -> bool {
                S prod = 1;
                S val = a;
                for (auto i = 0; i < len; ++i) {
                    prod *= val;
                    val += d;
                }
                return prod <= N;
            };
            if (!pred(1)) {
                break;
            }
            auto it = ranges::partition_point(views::iota(1LL, (i64)1e9), pred);
            auto max_d = *(it - 1);
            ans += max_d;
        }
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
