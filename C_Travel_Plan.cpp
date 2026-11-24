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

using Z = modint<998244353>;
using S = array<vector<Z>, 2>;

map<i64, S> dp;

vector<Z> add(vector<Z> a, vector<Z> b) {
    if (size(a) < size(b))
        swap(a, b);
    for (auto i = 0; i < ssize(b); ++i) {
        a[i] += b[i];
    }
    return a;
}

vector<Z> conv(vector<Z> a, vector<Z> b) {
    auto n = ssize(a);
    auto m = ssize(b);
    vector<Z> c(n + m - 1);
    for (auto i = 0; i < n; ++i) {
        for (auto j = 0; j < m; ++j) {
            c[i + j] += a[i] * b[j];
        }
    }
    return c;
}

S F(i64 n) {
    if (n == 0)
        return {};
    if (n == 1)
        return {{{1}, {0, 1}}};
    if (auto it = dp.find(n); it != dp.end())
        return it->second;
    auto a = 0;
    while ((1LL << (a + 1)) - 1 < n) {
        a++;
    }
    auto s = n - (1LL << a) + 1;
    auto l = (1LL << (a - 1)) - 1 + min(1LL << (a - 1), s);
    auto r = (1LL << (a - 1)) - 1 + max(0LL, s - (1LL << (a - 1)));
    auto [fl, gl] = F(l);
    auto [fr, gr] = F(r);
    vector<Z> g{1};
    g = add(g, gl);
    g = add(g, gr);
    auto f = add(fl, fr);
    f = add(f, g);
    f = add(f, conv(gl, gr));
    g.insert(g.begin(), 0);
    return dp[n] = {f, g};
}

#define TC
void solve() {
    i64 N, M;
    cin >> N >> M;
    auto f = F(N)[0];
    Z ans = 0;
    for (auto i = 0; i < ssize(f); ++i) {
        Z c = 0;
        for (auto k = 1; k <= M; ++k) {
            c += k * (Z(k).pow(i + 1) - Z(k - 1).pow(i + 1));
        }
        ans += c * f[i] * Z(M).pow(N - i - 1);
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
