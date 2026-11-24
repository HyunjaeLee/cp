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

#ifndef LINEAR_SIEVE_HPP
#define LINEAR_SIEVE_HPP

#include <cassert>
#include <map>
#include <vector>

struct linear_sieve {
    explicit linear_sieve(int n) : lpf(n + 1) {
        for (auto i = 2; i <= n; ++i) {
            if (lpf[i] == 0) {
                lpf[i] = i;
                primes.push_back(i);
            }
            for (auto p : primes) {
                if (lpf[i] < p || n < 1LL * i * p) {
                    break;
                }
                lpf[i * p] = p;
            }
        }
    }
    std::map<int, int> factorize(int x) const { // O(log x)
        assert(1 <= x && x < int(lpf.size()));
        std::map<int, int> f;
        while (1 < x) {
            ++f[lpf[x]];
            x /= lpf[x];
        }
        return f;
    }
    bool is_prime(int x) const { // O(1)
        assert(1 <= x && x < int(lpf.size()));
        return lpf[x] == x;
    }
    std::vector<int> lpf;
    std::vector<int> primes;
};

#endif // LINEAR_SIEVE_HPP

#include <atcoder/segtree>

constexpr auto inf = numeric_limits<int>::max() / 2;

int op(int a, int b) { return min(a, b); }

int e() { return inf; }

#define TC
void solve() {
    int N;
    cin >> N;
    vector<int> A(N);
    read(A);
    linear_sieve sieve(N + 123);
    vector<i64> X;
    for (auto i = 0; i < N; ++i) {
        for (auto [p, e] : sieve.factorize(A[i])) {
            i64 x = 1;
            for (auto j = 0; j <= e; ++j) {
                x *= p;
                X.push_back(x);
            }
        }
    }
    for (auto p : sieve.primes) {
        X.push_back(p);
    }
    ranges::sort(X);
    X.erase(unique(begin(X), end(X)), end(X));
    atcoder::segtree<int, op, e> seg(vector<int>(X.size(), -1));
    set<i64> ans;
    for (auto i = 0; i < N; ++i) {
        for (auto [p, e] : sieve.factorize(A[i])) {
            i64 x = 1;
            for (auto j = 0; j < e; ++j) {
                x *= p;
                auto id = int(ranges::lower_bound(X, x) - X.begin());
                if (0 < i - seg.get(id) - 1 && seg.get(id) < seg.prod(0, id)) {
                    ans.insert(x);
                }
            }
        }
        for (auto [p, e] : sieve.factorize(A[i])) {
            i64 x = 1;
            for (auto j = 0; j < e; ++j) {
                x *= p;
                auto id = int(ranges::lower_bound(X, x) - X.begin());
                seg.set(id, i);
            }
        }
    }
    for (auto i = 0; i < int(X.size()); ++i) {
        if (0 < N - seg.get(i) - 1 && seg.get(i) < seg.prod(0, i)) {
            ans.insert(X[i]);
        }
    }
    cout << size(ans) << "\n";
    show(ans);
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
