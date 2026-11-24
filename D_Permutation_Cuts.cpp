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

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N - 1);
    read(A);
    if (ranges::max(A) != N - 1) {
        cout << "0\n";
        return;
    }
    vector<pair<int, int>> v{{A[0], 1}};
    for (auto i = 1; i < N - 1; ++i) {
        if (A[i - 1] == A[i]) {
            v.back().second++;
        } else {
            v.emplace_back(A[i], 1);
        }
    }
    {
        auto u = v;
        ranges::sort(u);
        for (auto i = 0; i < int(u.size()) - 1; ++i) {
            if (u[i].first == u[i + 1].first) {
                cout << "0\n";
                return;
            }
        }
    }
    {
        auto p = int(ranges::max_element(v) - begin(v));
        for (auto i = 0; i < p; ++i) {
            if (v[i] >= v[i + 1]) {
                cout << "0\n";
                return;
            }
        }
        for (auto i = p; i < int(v.size()) - 1; ++i) {
            if (v[i] <= v[i + 1]) {
                cout << "0\n";
                return;
            }
        }
    }
    ranges::sort(v);
    auto cnt = 0;
    Z ans = 2;
    Combinatorics<Z> C;
    for (auto [x, g] : v) {
        ans *= C(x - 1 - cnt, g - 1) * C.f(g - 1);
        cnt += g;
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
