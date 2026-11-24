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
    int ans, len_l, len_r, val_l, val_r, len;
};

S op(S a, S b) {
    if (b.ans == -1)
        return a;
    if (a.ans == -1)
        return b;
    S c;
    c.ans = max(a.ans, b.ans);
    c.len_l = a.len_l;
    c.val_l = a.val_l;
    c.len_r = b.len_r;
    c.val_r = b.val_r;
    c.len = a.len + b.len;
    if (a.val_r == b.val_l) {
        c.ans = max(c.ans, a.len_r + b.len_l);
        if (a.ans == a.len) {
            c.len_l = a.len + b.len_l;
        }
        if (b.ans == b.len) {
            c.len_r = b.len + a.len_r;
        }
    }
    return c;
}

S e() { return {-1, -1, -1, -1, -1, -1}; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    atcoder::segtree<S, op, e> seg(N);
    for (auto i = 0; i < N; ++i) {
        int x;
        cin >> x;
        seg.set(i, {1, 1, 1, x, x, 1});
    }
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            --i;
            seg.set(i, {1, 1, 1, x, x, 1});
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            auto ans = seg.prod(l, r).ans;
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
