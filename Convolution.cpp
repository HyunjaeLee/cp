#include <bits/stdc++.h>
using namespace std;

// clang-format off
using i8 = signed char; using u8 = unsigned char;
using i32 = int;        using u32 = unsigned;
using i64 = long long;  using u64 = unsigned long long;
using i128 = __int128;  using u128 = unsigned __int128;
template <typename T> T ceil_div(T a, T b) { return a / b + static_cast<T>((a ^ b) > 0 && a % b != 0); }
template <typename T> T floor_div(T a, T b) { return a / b - static_cast<T>((a ^ b) < 0 && a % b != 0); }
void read(auto &a) { for (auto &x : a) { int x_; cin >> x_; x = x_; } }
void show(const auto &a, string_view sep = " ", string_view end = "\n") {
    for (auto it = a.begin(); it != a.end(); ++it) { if (it != a.begin()) { cout << sep; }
    auto x = *it; cout << x.val(); } cout << end;
}
// clang-format on

template <signed_integral auto mod> struct modint {
    using T = decltype(mod);
    static_assert(0 < mod && mod <= numeric_limits<T>::max() / 2 + 1);
    modint() : v(0) {}
    modint(integral auto x) : v(T((x % mod + mod) % mod)) {}
    modint &operator+=(modint o) { return v = (v + o.v) % mod, *this; }
    modint &operator-=(modint o) { return v = (v - o.v + mod) % mod, *this; }
    modint &operator*=(modint o) { return v = T(i128(v) * o.v % mod), *this; }
    modint &operator/=(modint o) { return *this *= o.inv(); }
    modint operator-() { return -v; }
    modint operator+() { return *this; }
    friend modint operator+(modint l, modint r) { return l += r; }
    friend modint operator-(modint l, modint r) { return l -= r; }
    friend modint operator*(modint l, modint r) { return l *= r; }
    friend modint operator/(modint l, modint r) { return l /= r; }
    friend bool operator==(modint, modint) = default;
    modint pow(integral auto n) { assert(0 <= n);
        modint x = *this, r = 1;
        for (; n; x *= x, n /= 2) if (n & 1) r *= x;
        return r;
    }
    modint inv() { // gcd(v, mod) = 1
        T a = v, b = mod, s = 1, t = 0;
        while (b) {
            T q = a / b;
            swap(a -= b * q, b);
            swap(s -= t * q, t);
        }
        assert(a == 1);
        return s;
    }
    T val() { return v; }
    private: T v;
};

const int R = 3, A = 119, B = 23, MOD = A << B | 1; // MOD = 998244353
using Z = modint<MOD>;

void NTT(vector<Z> &a, bool invert) {
    int N = a.size();
    for (int i = 1, j = 0; i < N; i++) {
        int bit = N >> 1;
        for (; j >= bit; bit >>= 1)
            j -= bit;
        j += bit;
        if (i < j)
            swap(a[i], a[j]);
    }
    Z ang = invert ? Z(R).inv() : R;
    for (int len = 2; len <= N; len <<= 1) {
        Z wlen = ang.pow((A << B) / len);
        for (int i = 0; i < N; i += len) {
            Z w = 1;
            for (int j = 0; j < len >> 1; j++) {
                Z u = a[i | j], v = a[i | j | len >> 1] * w;
                a[i | j] = u + v;
                a[i | j | len >> 1] = u - v;
                w *= wlen;
            }
        }
    }
    if (invert) {
        Z j = Z(N).inv();
        for (Z &x : a)
            x *= j;
    }
}

vector<Z> operator*(vector<Z> a, vector<Z> b) {
    int N = 1, na = a.size(), nb = b.size();
    while (N < na + nb - 1)
        N <<= 1;
    a.resize(N);
    b.resize(N);
    NTT(a, false), NTT(b, false);
    for (int i = 0; i < N; ++i)
        a[i] *= b[i];
    NTT(a, true);
    return a;
}

void solve() {
    int N, M;
    cin >> N >> M;
    vector<Z> a(N), b(M);
    read(a);
    read(b);
    auto c = a * b;
    c.resize(N + M - 1);
    show(c);
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
