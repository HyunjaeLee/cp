#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

#ifndef COMBINATORICS_HPP
#define COMBINATORICS_HPP

#include <algorithm>
#include <bit>
#include <cassert>
#include <vector>

template <typename Z> struct Combinatorics {
    static void grow(int n) {
        auto m = int(f_.size());
        if (n < m) {
            return;
        }
        n = std::min<int>(std::bit_ceil(unsigned(n + 1)), Z::mod());
        f_.resize(n);
        finv_.resize(n);
        for (auto i = m; i < n; ++i) {
            f_[i] = f_[i - 1] * Z(i);
        }
        finv_[n - 1] = f_[n - 1].inv();
        for (auto i = n - 1; m < i; --i) {
            finv_[i - 1] = finv_[i] * Z(i);
        }
    }
    static Z f(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return f_[n];
    }
    static Z finv(int n) { // O(1)
        assert(0 <= n);
        grow(n);
        return finv_[n];
    }
    static Z binom(int n, int k) { // O(1)
        if (0 <= k && k <= n) {
            return f(n) * finv(k) * finv(n - k);
        } else {
            return Z(0);
        }
    }
    static Z binom2(long long n, long long k) { // O(min(k, n - k))
        if (k < 0 || n < k) {
            return Z(0);
        }
        if (n - k < k) {
            return binom2(n, n - k);
        }
        auto ret = finv(int(k));
        for (auto i = 0; i < k; ++i) {
            ret *= Z(n - i);
        }
        return ret;
    }
    Z operator()(int n, int k) { return binom(n, k); }

private:
    inline static std::vector<Z> f_{Z(1)}, finv_{Z(1)};
};

#endif // COMBINATORICS_HPP

void solve() {
    int N, K;
    cin >> N >> K;
    vector<int> A(N);
    read(A);
    ranges::sort(A);
    Combinatorics<Z> C;
    Z ans = 0;
    for (auto c = 0; c < N; ++c) {
        for (auto p = 0; p < N; ++p) {
            auto small = c;         // 나보다 작은 애들 개수
            auto large = N - c - 1; // 나보다 큰 애들 개수
            auto l = max(0, p - K);
            auto r = min(N - 1, p + K);
            Z ways1 = 0;
            Z ways2 = 0;
            auto fixed = 1;
            for (auto s = l; s <= r; ++s) {
                if (s == p) {
                    fixed = 0;
                    continue;
                }
                Z w1 = C(small, 1) * C(large, s - l - !fixed) * C.f(s - l - !fixed) * C.f(N - (s - l + 1 + fixed));
                ways1 += w1;
                if (s + K + 1 <= r) {
                    Z w2 = C(small, 1) * C(large, s - l) * C.f(s - l) * C(large - (s - l), K - 1) * C.f(K - 1) *
                           C.f(N - (s + K + 1 - l));
                    Z w3 = C(small, 1) * C(large, s - l) * C.f(s - l) * C(large - (s - l), r - s - 1) * C.f(r - s - 1) *
                           C.f(N - (r - l + 1));
                    w1 += w2 - w3;
                    ways2 += w2 - w3;
                }
                ans += A[c] * w1;
            }
        }
    }
    cout << ans.val() << "\n";
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
