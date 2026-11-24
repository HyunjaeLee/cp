#include <bits/stdc++.h>

// https://github.com/hitonanode/cplib-cpp/blob/master/rational/rational_number.hpp
template <typename T, bool reduce = false> struct rational {
    constexpr rational(T num = 0, T den = 1) : p(num), q(den) { normalize(); }

    constexpr bool is_finite() const { return q != 0; }
    constexpr bool is_infinite() const { return p != 0 && q == 0; }
    constexpr bool is_nan() const { return p == 0 && q == 0; }

    constexpr rational &operator+=(const rational &o) {
        if (is_nan() || o.is_nan())
            return *this = rational(0, 0);
        if (is_infinite() && o.is_infinite())
            return *this = rational(p + o.p, 0);
        return *this = rational(p * o.q + q * o.p, q * o.q);
    }
    constexpr rational &operator-=(const rational &o) {
        if (is_nan() || o.is_nan())
            return *this = rational(0, 0);
        if (is_infinite() && o.is_infinite())
            return *this = rational(p - o.p, 0);
        return *this = rational(p * o.q - q * o.p, q * o.q);
    }
    constexpr rational &operator*=(const rational &o) { return *this = rational(p * o.p, q * o.q); }
    constexpr rational &operator/=(const rational &o) {
        if (o.p < 0)
            return *this = rational(p * -o.q, -q * o.p);
        return *this = rational(p * o.q, q * o.p);
    }

    friend constexpr rational operator+(rational a, const rational &b) { return a += b; }
    friend constexpr rational operator-(rational a, const rational &b) { return a -= b; }
    friend constexpr rational operator*(rational a, const rational &b) { return a *= b; }
    friend constexpr rational operator/(rational a, const rational &b) { return a /= b; }

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
            return std::partial_ordering::unordered;
        }
        if (is_infinite() && r.is_infinite()) {
            return p <=> r.p;
        }
        if (is_infinite()) {
            return p < 0 ? std::partial_ordering::less : std::partial_ordering::greater;
        }
        if (r.is_infinite()) {
            return r.p < 0 ? std::partial_ordering::greater : std::partial_ordering::less;
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
            x->p = rational<T>(y->b - x->b, x->a - y->a);
        }
        return x->p >= y->p;
    }
    void add(T a, T b) {
        if constexpr (!maximize) {
            a = -a;
            b = -b;
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
    std::pair<T, T> query_line(auto x) const {
        assert(!lines.empty());
        auto l = lines.lower_bound(x);
        if constexpr (maximize) {
            return {l->a, l->b};
        } else {
            return {-l->a, -l->b};
        }
    }
    T query(T x) const {
        auto [a, b] = query_line(x);
        return a * x + b;
    }

private:
    std::multiset<line, std::less<>> lines;
};

int main() {
    std::cin.tie(0)->sync_with_stdio(0);
    int N, Q;
    std::cin >> N >> Q;
    line_container<long long, false> lc;
    for (auto i = 0; i < N; ++i) {
        long long a, b;
        std::cin >> a >> b;
        lc.add(a, b);
    }
    while (Q--) {
        int t;
        std::cin >> t;
        if (t == 0) {
            long long a, b;
            std::cin >> a >> b;
            lc.add(a, b);
        } else {
            int x;
            std::cin >> x;
            std::cout << lc.query(x) << "\n";
        }
    }
}
