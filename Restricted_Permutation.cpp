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
void read(auto &a) { for (auto &x : a) cin >> x; }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) {
        if (it != a.begin()) cout << sep;
        cout << *it;
    }
    cout << end;
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

#include <atcoder/modint>
using Z = atcoder::modint998244353;

void solve() {
    int N;
    string S;
    cin >> N >> S;
    if (S[0] != 'o' || S[N - 1] != 'o') {
        cout << "0\n";
        return;
    }
    vector<Z> dp(N + 1);
    dp[2] = 2;
    Combinatorics<Z> C;
    for (auto i = 3; i <= N; ++i) {
        dp[i] = C.f(i);
        for (auto j = 2; j < i; ++j) {
            dp[i] -= dp[j] * C.f(i - j + 1);
        }
    }
    vector<int> I;
    for (auto i = 0; i < N; ++i) {
        if (S[i] == 'o') {
            I.push_back(i);
        }
    }
    Z ans = 1;
    for (auto i = 0; i < int(I.size()) - 1; ++i) {
        ans *= dp[I[i + 1] - I[i] + 1];
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
