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

#ifndef MODINT_HPP
#define MODINT_HPP

#include <cassert>
#include <concepts>
#include <iostream>
#include <limits>
#include <type_traits>
#include <utility>

template <std::signed_integral auto mod> struct modint {
    using T = decltype(mod);
    static_assert(0 < mod && mod <= std::numeric_limits<T>::max() / 2 + 1);
    constexpr modint() : v(0) {}
    constexpr modint(std::integral auto x) : v(T((x % mod + mod) % mod)) {}
    constexpr modint &operator+=(modint o) {
        v = (v + o.v) % mod;
        return *this;
    }
    constexpr modint &operator-=(modint o) {
        v = (v - o.v + mod) % mod;
        return *this;
    }
    constexpr modint &operator*=(modint o) {
        static_assert(sizeof(T) <= sizeof(long long));
        using U = std::conditional_t<sizeof(T) <= sizeof(int), long long, __int128>;
        v = T(U(v) * o.v % mod);
        return *this;
    }
    constexpr modint &operator/=(modint o) { return *this *= o.inv(); }
    constexpr modint operator-() const { return -v; }
    constexpr modint operator+() const { return *this; }
    friend constexpr modint operator+(modint l, modint r) { return l += r; }
    friend constexpr modint operator-(modint l, modint r) { return l -= r; }
    friend constexpr modint operator*(modint l, modint r) { return l *= r; }
    friend constexpr modint operator/(modint l, modint r) { return l /= r; }
    friend bool operator==(modint, modint) = default;
    constexpr modint pow(std::integral auto n) const {
        assert(0 <= n);
        modint x = *this, r = 1;
        for (; n; x *= x, n /= 2) {
            if (n & 1) {
                r *= x;
            }
        }
        return r;
    }
    constexpr modint inv() const {
        T a = v, b = mod, s = 1, t = 0;
        while (b) {
            T q = a / b;
            std::swap(a -= b * q, b);
            std::swap(s -= t * q, t);
        }
        assert(a == 1);
        return s;
    }
    constexpr T val() const { return v; }
    friend std::ostream &operator<<(std::ostream &os, modint a) { return os << a.v; }
    friend std::istream &operator>>(std::istream &is, modint &a) {
        long long x;
        is >> x;
        a = x;
        return is;
    }

private:
    T v;
};

using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

#endif // MODINT_HPP

struct S {
    bool operator<(S o) const {
        if (k == o.k)
            return x < o.x;
        if (k < 30 && o.k < 30)
            return (1 << k) + x < (1 << o.k) + o.x;
        return k < o.k;
    }
    bool operator==(S o) const { return !(*this < o) && !(o < *this); }
    static S inf() {
        constexpr auto INF = numeric_limits<int>::max() / 2;
        return {INF, INF};
    }
    int k, x;
};

using Z = modint998244353;

void solve() {
    int N, M;
    cin >> N >> M;
    vector<vector<int>> G(2 * N);
    for (auto i = 0; i < M; ++i) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        G[u].push_back(v);
        G[N + v].push_back(N + u);
    }
    priority_queue<pair<S, int>, vector<pair<S, int>>, greater<>> pq;
    vector<S> dist(N, S::inf());
    dist[0] = {0, 0};
    pq.emplace(dist[0], 0);
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();
        if (d != dist[u])
            continue;
        if ( S nd = {d.k + 1, d.x}; )
        for (auto v : G[u]) {
            S nd = {d.k, d.x + 1};
            if (nd < dist[v]) {
                dist[v] = nd;
                pq.emplace(dist[v], v);
            }
        }
    }
    auto ans = Z(2).pow(dist[N - 1].k) - 1 + dist[N - 1].x;
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
