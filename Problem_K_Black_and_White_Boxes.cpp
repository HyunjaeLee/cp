#include <bits/stdc++.h>
using namespace std;

using i64 = long long;
using u64 = unsigned long long;
using i128 = __int128;

// g > 0: L wins
// g < 0: R wins
// g = 0: second wins
struct Surreal {
    using S = Surreal;
    i64 p, q; // p / 2^q
    Surreal(i64 p_ = 0, i64 q_ = 0) : p(p_), q(q_) {
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
        while (!(lmax < u && u < rmin))
            u = lmax < u ? u.left() : u.right();
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
};

// G : 0 = G and 0 : G = G
// Ordinal sum is associative: (G : H) : J = G : (H : J)
// ordinal sum of numbers where the base is in canonical form
Surreal ordinal_sum(Surreal g, Surreal h) {
    using S = Surreal;
    if (h == 0) return g;
    if (g == 0) return h;
    // If G and H are positions, −(G : H) = (−G) : (−H).
    if (g < 0) return -ordinal_sum(-g, -h);
    auto n = abs(g.p) >> g.q, a = abs(g.p) & ((1LL << g.q) - 1), p = g.q;
    auto m = abs(h.p) >> h.q, b = abs(h.p) & ((1LL << h.q) - 1), q = h.q;
    if (a == 0) {
        if (0 <= h)
            return S(n) + S(m) + S(b, q);
        else
            return S(n) - S(1) + S(1, m) - S(b, m + q + 1);
    } else {
        if (0 <= h)
            return S(n) + S(a + 1, p) - S(1, p + m) + S(b, p + m + q + 1);
        else
            return S(n) + S(a - 1, p) + S(1, p + m) - S(b, p + m + q + 1);
    }
}

int main() {
    cin.tie(0)->sync_with_stdio(0);
    using S = Surreal;
    int N;
    cin >> N;
    vector<string> A(N);
    for (auto i = 0; i < N; ++i) {
        cin >> A[i];
    }
    vector<S> G(N);
    for (auto i = 0; i < N; ++i) {
        for (auto c : A[i]) {
            G[i] = ordinal_sum(G[i], c == 'B' ? 1 : -1);
        }
    }
    auto ans = 0;
    auto X = N / 2;
    auto Y = N - N / 2;
    map<S, int> mp;
    for (auto s = 0; s < (1 << X); ++s) {
        S sum = 0;
        auto sz = 0;
        for (auto i = 0; i < X; ++i) {
            if ((s >> i) & 1) {
                sum += G[i];
                sz += int(A[i].size());
            }
        }
        mp[sum] = max(mp[sum], sz);
    }
    for (auto s = 0; s < (1 << Y); ++s) {
        S sum = 0;
        auto sz = 0;
        for (auto i = 0; i < Y; ++i) {
            if ((s >> i) & 1) {
                sum += G[X + i];
                sz += int(A[X + i].size());
            }
        }
        if (auto it = mp.find(-sum); it != mp.end()) {
            ans = max(ans, it->second + sz);
        }
    }
    cout << ans << "\n";
}
