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

pair<int, Z> F(int m) {
    assert(2 <= m);
    Z cnt = 0;
    Combinatorics<Z> C;
    for (auto a = 0; a <= m / 2; ++a) {
        if ((m - 2 * a) % 3 == 0) {
            auto b = (m - 2 * a) / 3;
            cnt += C(a + b, a);
        }
    }
    return {2 * m, cnt};
}

Z dp[5050];

#define TC
void solve() {
    int N;
    string S;
    cin >> N >> S;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = S[i] - '0';
    }
    vector<vector<int>> G;
    for (auto i = 0; i < N; ++i) {
        if (G.empty() || G.back().back() == A[i]) {
            G.push_back({A[i]});
        } else {
            G.back().push_back(A[i]);
        }
    }
    auto cost = 0;
    Z num = 1;
    array<int, 2> X{};
    for (const auto &g : G) {
        if (g.size() == 1) {
            cost += 1;
            X[g[0]]++;
        } else {
            auto [p, q] = F(int(size(g)));
            cost += p;
            num *= q;
        }
    }
    num *= dp[X[0]] * dp[X[1]];
    cout << cost << " " << num.val() << "\n";
}

void init() {
    dp[0] = 1;
    Combinatorics<Z> C;
    for (auto i = 1; i < ssize(dp); ++i) {
        for (auto j = 0; j < i; ++j) {
            dp[i] += dp[j] * C(i - 1, j);
        }
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    init();
    int t = 1;
#ifdef TC
    cin >> t;
#endif
    for (auto i = 0; i < t; ++i) {
        solve();
    }
}
