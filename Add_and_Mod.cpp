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

struct S {
    bool has_zero;
    i64 u, v;
};

S op(S a, S b) {
    if (b.has_zero) {
        return {a.has_zero || b.has_zero, a.u + a.v + b.u, b.v};
    } else {
        return {a.has_zero || b.has_zero, a.u, a.v + b.v};
    }
}

S e() { return {false, 0, 0}; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    atcoder::segtree<S, op, e> seg(N);
    for (auto i = 0; i < N; ++i) {
        seg.set(i, {A[i] == 0, 0, A[i]});
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            --i;
            seg.set(i, {x == 0, 0, x});
        } else {
            int l, r, x;
            cin >> l >> r >> x;
            --l;
            auto [has_zero, u, v] = seg.prod(l, r);
            i64 ans;
            if (has_zero) {
                ans = (x + u) % 998244353 + v;
            } else {
                ans = x + v;
            }
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
