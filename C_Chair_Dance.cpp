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

#ifndef EXTGCD_HPP
#define EXTGCD_HPP

template <typename T> T extgcd(T a, T b, T &x, T &y) {
    if (b == 0) {
        x = 1, y = 0;
        return a;
    }
    T d = extgcd(b, a % b, y, x);
    y -= a / b * x;
    return d;
}

#endif // EXTGCD_HPP

void solve() {
    i64 N, Q;
    cin >> N >> Q;
    vector<i64> f(N); // chair -> person
    ranges::iota(f, 0);
    i64 M = N;
    i64 a = 1, b = 0;
    i64 pivot = 0;
    auto apply = [&](i64 c, i64 d) {
        a = (a * c) % N;
        b = (b * c + d) % N;
    };
    auto dist = [&](i64 i, i64 j) { return (N + j - i) % N; };
    constexpr auto inf = numeric_limits<i64>::max() / 4;
    auto go = [&](i64 x) {
        M /= gcd(x, M);
        vector<i64> g(N, -1), d(N, inf);
        for (auto i = 0; i < N; ++i) {
            if (f[i] == -1)
                continue;
            auto p = (a * i + b) % N;
            auto q = p * x % N;
            if (dist(p, q) < d[q]) {
                d[q] = dist(p, q);
                g[q] = f[i];
            }
        }
        swap(f, g);
        a = 1, b = 0;
        for (auto i = 0; i < N; ++i) {
            if (0 <= f[i]) {
                pivot = i;
                break;
            }
        }
    };
    auto inv = [&](i64 e) {
        i64 x, y;
        auto g = extgcd(e, M, x, y);
        assert(g == 1);
        return (M + x) % M;
    };
    auto who = [&](i64 x) -> i64 {
        auto p = (a * pivot + b) % N;
        if (x % (N / M) != p % (N / M))
            return -1;
        auto t = (N + x - p) / (N / M) * inv(a) % M;
        auto i = (pivot + (N / M) * t) % N;
        return f[i];
    };
    while (Q--) {
        char op;
        i64 x;
        cin >> op >> x;
        if (op == '+') {
            apply(1, x);
        } else if (op == '*') {
            if (gcd(x, M) == 1) {
                apply(x, 0);
            } else {
                go(x);
            }
        } else {
            auto ans = who(x % N);
            if (ans == 0)
                ans = N;
            cout << ans << "\n";
        }
    }
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
