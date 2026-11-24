#include <atcoder/lazysegtree>
#include <atcoder/modint>
#include <bits/stdc++.h>
using namespace std;
using Z = atcoder::modint998244353;

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

using S = array<Z, 5>;

S op(S a, S b) {
    S c;
    for (auto i = 0; i < 5; ++i) {
        c[i] = a[i] + b[i];
    }
    return c;
}

S e() { return {}; }

using F = Z;

S mapping(F f, S x) {
    S v;
    v[4] = x[4] + 4 * f * x[3] + 6 * f * f * x[2] + 4 * f * f * f * x[1] + f * f * f * f * x[0];
    v[3] = x[3] + 3 * f * x[2] + 3 * f * f * x[1] + f * f * f * x[0];
    v[2] = x[2] + 2 * f * x[1] + f * f * x[0];
    v[1] = x[1] + f * x[0];
    v[0] = x[0];
    return v;
}

F composition(F f, F g) { return f + g; }

F id() { return 0; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(N);
    auto f = [&](Z x) {
        S v;
        v[0] = 1;
        for (auto j = 1; j < 5; ++j) {
            v[j] = v[j - 1] * x;
        }
        return v;
    };
    for (auto i = 0; i < N; ++i) {
        int x;
        cin >> x;
        seg.set(i, f(x));
    }
    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        if (t == 1) {
            int x;
            cin >> x;
            seg.apply(l, r, x);
        } else {
            int k;
            cin >> k;
            auto ans = seg.prod(l, r)[k];
            cout << ans.val() << "\n";
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
