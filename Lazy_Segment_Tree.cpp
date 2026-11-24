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

constexpr auto inf = numeric_limits<i64>::max() / 2;

i64 op(i64 a, i64 b) { return min(a, b); }

i64 e() { return inf; }

i64 mapping(i64 f, i64 x) { return f + x; }

i64 composition(i64 f, i64 g) { return f + g; }

i64 id() { return 0; }

#include <atcoder/lazysegtree>

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N);
    read(A);
    atcoder::lazy_segtree<i64, op, e, i64, mapping, composition, id> seg(A);
    while (Q--) {
        int t, l, r;
        cin >> t >> l >> r;
        --l;
        if (t == 1) {
            i64 x;
            cin >> x;
            seg.apply(l, r, x);
        } else {
            cout << seg.prod(l, r) << "\n";
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
