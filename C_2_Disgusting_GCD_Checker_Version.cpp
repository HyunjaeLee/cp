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

linear_sieve sieve(200000);

#define TC
void solve() {
    int a, b;
    cin >> a >> b;
    if (a == b) {
        cout << "0\n";
        return;
    }
    if (gcd(a, b - a) == 1) {
        cout << "1\n";
        cout << b - a << "\n";
        return;
    }
    auto ok = [&](vector<int> xs) {
        auto u = a, v = b;
        for (auto x : xs) {
            if (gcd(u, x) != 1) {
                return false;
            }
            u += x;
        }
        return u == v;
    };
    constexpr auto G = 300;
    if (b - a <= G) {
        for (auto x = 1; x <= b - a; ++x) {
            auto y = b - a - x;
            if (ok({x, y})) {
                cout << "2\n";
                show(vector{x, y});
                return;
            }
        }
        for (auto x = 1; x <= b - a; ++x) {
            for (auto y = 1; x + y <= b - a; ++y) {
                auto z = b - a - x - y;
                if (ok({x, y, z})) {
                    cout << "3\n";
                    show(vector{x, y, z});
                    return;
                }
            }
        }
        assert(0);
    }
    auto it = ranges::upper_bound(sieve.primes, a);
    auto p = *it;
    auto x = p - a;
    auto y = b - p;
    cout << "2\n";
    show(vector{x, y});
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
