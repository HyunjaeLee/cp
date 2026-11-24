#include <atcoder/segtree>
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

constexpr auto inf = numeric_limits<i64>::max() / 4;

using S = array<i64, 25>;

S op(S a, S b) {
    S c;
    ranges::fill(c, -inf);
    for (auto i = 0; i < 5; ++i) {
        for (auto j = 0; j < 5; ++j) {
            for (auto k = 0; k < 5; ++k) {
                c[i * 5 + j] = max(c[i * 5 + j], a[i * 5 + k] + b[k * 5 + j]);
            }
        }
    }
    return c;
}

S e() {
    S a;
    ranges::fill(a, -inf);
    for (auto i = 0; i < 5; ++i) {
        a[i * 5 + i] = 0;
    }
    return a;
}

void solve() {
    int N;
    cin >> N;
    vector<i64> A(N), B(N);
    read(A);
    read(B);
    auto F = [&](int i) {
        S M;
        ranges::fill(M, -inf);
        M[0 * 5 + 0] = 0;
        M[0 * 5 + 1] = A[i] + B[i];
        M[0 * 5 + 2] = A[i] + 2 * B[i];

        M[1 * 5 + 1] = A[i];
        M[1 * 5 + 2] = A[i] + B[i];

        M[2 * 5 + 2] = 0;
        M[2 * 5 + 3] = A[i] + B[i];
        M[2 * 5 + 4] = A[i] + 2 * B[i];

        M[3 * 5 + 3] = A[i];
        M[3 * 5 + 4] = A[i] + B[i];

        M[4 * 5 + 4] = 0;
        return M;
    };
    vector<S> X(N);
    for (auto i = 0; i < N; ++i) {
        X[i] = F(i);
    }
    atcoder::segtree<S, op, e> seg(X);
    int Q;
    cin >> Q;
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p, x;
            cin >> p >> x;
            --p;
            A[p] = x;
            seg.set(p, F(p));
        } else if (t == 2) {
            int p, x;
            cin >> p >> x;
            --p;
            B[p] = x;
            seg.set(p, F(p));
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            auto M = seg.prod(l, r);
            auto ans = M[0 * 5 + 4];
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
