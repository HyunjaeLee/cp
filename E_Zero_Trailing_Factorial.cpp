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

linear_sieve sieve(10'000'000);

#define TC
void solve() {
    int N, M;
    cin >> N >> M;
    auto P = *prev(ranges::upper_bound(sieve.primes, N));
    auto V = [&](int x, int p) {
        i64 sum = 0;
        i64 y = p;
        while (0 < x / y) {
            sum += x / y;
            y *= p;
        }
        return sum;
    };
    i64 ans = 0;
    set<int> S;
    for (auto a : views::iota(P, N + 1)) {
        while (1 < a) {
            S.insert(sieve.lpf[a]);
            a /= sieve.lpf[a];
        }
    }
    for (auto x = P; x < N; ++x) {
        i64 val = numeric_limits<i64>::max();
        for (auto p : S) {
            auto u = V(x, p);
            auto v = V(N, p);
            i64 prod = p;
            for (i64 e = 1; e <= v && prod <= M; ++e) {
                if (u / e < v / e) {
                    val = min(val, u / e);
                }
                prod *= p;
            }
        }
        ans += val;
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
