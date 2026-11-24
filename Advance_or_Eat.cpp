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

// g > 0: L wins
// g < 0: R wins
// g = 0: second wins
// https://nyaannyaan.github.io/library/game/surreal-number.hpp
struct Surreal {
    using S = Surreal;
    i64 p, q; // p / 2^q

    Surreal(i64 p_ = 0, i64 q_ = 0) : p(p_), q(q_) {
        // normalize
        if (p) {
            auto k = min<i64>(countr_zero(u64(p)), q);
            p >>= k;
            q -= k;
        } else {
            q = 0;
        }
    }
    Surreal(const vector<S> &l, const vector<S> &r) {
        constexpr auto inf = numeric_limits<i64>::max();
        S lmax = l.empty() ? -inf : ranges::max(l);
        S rmin = r.empty() ? inf : ranges::min(r);
        assert(lmax < rmin);
        S u = 0;
        while (!(lmax < u && u < rmin)) {
            u = lmax < u ? u.left() : u.right();
        }
        *this = u;
    }

    friend S operator+(S l, S r) {
        auto cq = max(l.q, r.q);
        auto cp = (l.p << (cq - l.q)) + (r.p << (cq - r.q));
        return {cp, cq};
    }
    friend S operator-(S l, S r) {
        auto cq = max(l.q, r.q);
        auto cp = (l.p << (cq - l.q)) - (r.p << (cq - r.q));
        return {cp, cq};
    }
    S &operator+=(S r) { return *this = *this + r; }
    S &operator-=(S r) { return *this = *this - r; }

    S operator-() const { return {-p, q}; }
    S operator+() const { return *this; }

    friend strong_ordering operator<=>(S l, S r) { return l.p * (i128(1) << r.q) <=> r.p * (i128(1) << l.q); }
    friend bool operator==(S l, S r) { return l.p * (i128(1) << r.q) == r.p * (i128(1) << l.q); }

    S left() const { return *this - (p <= 0 && q == 0 ? 1 : S{1, q + 1}); }
    S right() const { return *this + (0 <= p && q == 0 ? 1 : S{1, q + 1}); }

    friend ostream &operator<<(ostream &os, S r) {
        os << r.p;
        if (r.q) {
            os << "/" << (1LL << r.q);
        }
        return os;
    }
};

// G : 0 = G and 0 : G = G
// Ordinal sum is associative: (G : H) : J = G : (H : J)
// https://arxiv.org/pdf/2305.16516
// ordinal sum of numbers where the base is in canonical form
Surreal ordinal_sum(Surreal g, Surreal h) {
    using S = Surreal;
    if (h == 0) {
        return g;
    }
    if (g == 0) {
        return h;
    }
    if (g < 0) {
        // If G and H are positions, −(G : H) = (−G) : (−H).
        return -ordinal_sum(-g, -h);
    }
    auto n = abs(g.p) >> g.q;
    auto a = abs(g.p) & ((1LL << g.q) - 1);
    auto p = g.q;
    auto m = abs(h.p) >> h.q;
    auto b = abs(h.p) & ((1LL << h.q) - 1);
    auto q = h.q;
    if (a == 0) {
        if (0 <= h) {
            return S(n) + S(m) + S(b, q);
        } else {
            return S(n) - S(1) + S(1, m) - S(b, m + q + 1);
        }
    } else {
        if (0 <= h) {
            return S(n) + S(a + 1, p) - S(1, p + m) + S(b, p + m + q + 1);
        } else {
            return S(n) + S(a - 1, p) + S(1, p + m) - S(b, p + m + q + 1);
        }
    }
}

void solve() {
    int N;
    cin >> N;
    vector<string> A(N);
    read(A);
    map<string, Surreal> memo;
    auto f = [&](this auto &&self, const string &s) -> Surreal {
        if (auto it = memo.find(s); it != memo.end()) {
            return it->second;
        }
        vector<Surreal> L, R;
        for (auto i = 1; i < N; ++i) {
            if (s[i] == 'W' && s[i - 1] == '.') {
                auto t = s;
                swap(t[i - 1], t[i]);
                L.push_back(self(t));
            }
        }
        for (auto i = 0; i < N; ++i) {
            if (s[i] == 'B') {
                auto t = s;
                t[i] = '.';
                L.push_back(self(t));
            }
        }
        for (auto i = 1; i < N; ++i) {
            if (s[i] == 'B' && s[i - 1] == '.') {
                auto t = s;
                swap(t[i - 1], t[i]);
                R.push_back(self(t));
            }
        }
        for (auto i = 0; i < N; ++i) {
            if (s[i] == 'W') {
                auto t = s;
                t[i] = '.';
                R.push_back(self(t));
            }
        }
        return memo[s] = Surreal{L, R};
    };
    Surreal sum = 0;
    for (auto j = 0; j < N; ++j) {
        string s;
        for (auto i = 0; i < N; ++i) {
            s += A[i][j];
        }
        sum += f(s);
    }
    if (0 < sum) {
        cout << "Takahashi\n";
    } else if (sum < 0) {
        cout << "Snuke\n";
    } else {
        cout << "Snuke\n";
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
