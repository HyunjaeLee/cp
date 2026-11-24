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

// https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp
template <typename T, bool reduce = false> struct rational {
    constexpr rational(T num = 0, T den = 1) : p(num), q(den) { normalize(); }

    constexpr bool is_finite() const { return q != 0; }
    constexpr bool is_infinite() const { return p != 0 && q == 0; }
    constexpr bool is_nan() const { return p == 0 && q == 0; }

    constexpr rational operator+(const rational &o) const {
        if (is_nan() || o.is_nan()) {
            return rational(0, 0);
        }
        if (is_infinite() && o.is_infinite()) {
            return rational(p + o.p, 0);
        }
        return rational(p * o.q + q * o.p, q * o.q);
    }
    constexpr rational operator-(const rational &o) const {
        if (is_nan() || o.is_nan()) {
            return rational(0, 0);
        }
        if (is_infinite() && o.is_infinite()) {
            return rational(p - o.p, 0);
        }
        return rational(p * o.q - q * o.p, q * o.q);
    }
    constexpr rational operator*(const rational &o) const { return rational(p * o.p, q * o.q); }
    constexpr rational operator/(const rational &o) const {
        if (o.p < 0) {
            return rational(p * -o.q, -q * o.p);
        }
        return rational(p * o.q, q * o.p);
    }
    constexpr rational &operator+=(const rational &o) { return *this = *this + o; }
    constexpr rational &operator-=(const rational &o) { return *this = *this - o; }
    constexpr rational &operator*=(const rational &o) { return *this = *this * o; }
    constexpr rational &operator/=(const rational &o) { return *this = *this / o; }
    constexpr rational operator-() const { return rational(-p, q); }
    constexpr rational abs() const { return rational(0 < p ? p : -p, q); }

    constexpr T floor() const {
        assert(is_finite());
        return floor_div(p, q);
    }
    constexpr T ceil() const {
        assert(is_finite());
        return ceil_div(p, q);
    }

    constexpr std::partial_ordering operator<=>(const rational &r) const {
        if (is_nan() || r.is_nan()) {
            return partial_ordering::unordered;
        }
        if (is_infinite() && r.is_infinite()) {
            return p <=> r.p;
        }
        if (is_infinite()) {
            return p < 0 ? partial_ordering::less : partial_ordering::greater;
        }
        if (r.is_infinite()) {
            return r.p < 0 ? partial_ordering::greater : partial_ordering::less;
        }
        using W = std::conditional_t<sizeof(T) <= sizeof(int), long long, __int128_t>;
        return (W(p) * r.q) <=> (W(r.p) * q);
    }
    constexpr bool operator==(const rational &r) const { return (*this <=> r) == 0; }

    constexpr explicit operator double() const { return (double)p / (double)q; }
    constexpr explicit operator long double() const { return (long double)p / (long double)q; }

    constexpr T numerator() const { return p; }
    constexpr T denominator() const { return q; }

private:
    constexpr void normalize() {
        if (q == 0) {
            p = (p > 0) - (p < 0);
            return;
        }
        if constexpr (reduce) {
            T g = __gcd(p, q);
            if (g) {
                p /= g;
                q /= g;
            }
        }
        if (q < 0) {
            p = -p;
            q = -q;
        }
    }

    T p, q; // 0 <= q
};

// https://github.com/kth-competitive-programming/kactl/blob/main/content/data-structures/LineContainer.h
template <typename T, bool maximize = true> struct line_container {
    struct line {
        T a, b;
        mutable rational<T> p;
        bool operator<(const line &o) const { return a < o.a; }
        bool operator<(auto x) const { return p < x; }
    };
    static constexpr auto inf = rational<T>(1, 0);
    bool isect(auto x, auto y) {
        if (y == lines.end()) {
            x->p = inf;
            return false;
        }
        if (x->a == y->a) {
            x->p = (y->b < x->b) ? inf : -inf;
        } else {
            x->p = (y->b - x->b) / (x->a - y->a);
        }
        return x->p >= y->p;
    }
    void add(T a, T b) {
        if (!maximize) {
            a *= -1, b *= -1;
        }
        auto z = lines.emplace(a, b, 0);
        auto y = z++;
        auto x = y;
        while (isect(y, z)) {
            z = lines.erase(z);
        }
        if (x != lines.begin() && isect(--x, y)) {
            y = lines.erase(y);
            isect(x, y);
        }
        while ((y = x) != lines.begin() && (--x)->p >= y->p) {
            isect(x, lines.erase(y));
        }
    }
    auto query(auto x) {
        assert(!lines.empty());
        auto l = *lines.lower_bound(x);
        auto y = l.a * x + l.b;
        return maximize ? y : -y;
    }

private:
    multiset<line, less<>> lines;
};

template <typename T> struct line_container_2d {
    void add(T a, T b) {
        max_lc.add(a, b);
        min_lc.add(a, b);
    }
    T max(T x, T y) {
        if (y == 0) {
            return x < 0 ? x * min_a : x * max_a;
        }
        rational<T> r(x, y);
        auto z = (y < 0 ? min_lc.query(r) : max_lc.query(r)) / y;
        return z.numerator() / z.denominator();
    }
    T min(T x, T y) { return -max(-x, -y); }
    static constexpr auto inf = numeric_limits<T>::max();
    T min_a = inf, max_a = -inf;
    line_container<T> max_lc;
    line_container<T, false> min_lc;
};

#define TC
void solve() {
    int N;
    cin >> N;
    vector<pair<int, int>> P(N + 1);
    vector<i64> pref(N + 1);
    for (auto i = 1; i <= N; ++i) {
        cin >> P[i].first >> P[i].second >> pref[i];
    }
    for (auto i = 0; i < N; ++i) {
        pref[i + 1] += pref[i];
    }
    constexpr auto inf = numeric_limits<i64>::max() / 2;
    vector<i64> dp(N + 1, inf);
    line_container_2d<i64> lc;
    auto D = [&](int i, int j) {
        auto dx = P[i].first - P[j].first;
        auto dy = P[i].second - P[j].second;
        return dx * dx + dy * dy;
    };
    for (auto i = N; 0 <= i; --i) {
        dp[i] = pref[N] - pref[i];
        for (auto j = i + 1; j <= N; ++j) {
            dp[i] = min(dp[i], pref[j - 1] - pref[i] + D(i, j) + dp[j]);
        }
        
    }
    cout << dp[0] << "\n";
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
