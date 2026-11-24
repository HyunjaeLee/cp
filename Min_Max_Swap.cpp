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

constexpr auto inf = numeric_limits<int>::max() / 2;

struct S {
    int min, max, min_pos, max_pos;
};

S op(S a, S b) {
    S c;
    if (a.min < b.min) {
        c.min = a.min;
        c.min_pos = a.min_pos;
    } else {
        c.min = b.min;
        c.min_pos = b.min_pos;
    }
    if (a.max > b.max) {
        c.max = a.max;
        c.max_pos = a.max_pos;
    } else {
        c.max = b.max;
        c.max_pos = b.max_pos;
    }
    return c;
}

S e() { return {inf, -inf, -1, -1}; }

void solve() {
    int N, M;
    cin >> N >> M;
    vector<int> A(N);
    read(A);
    atcoder::segtree<S, op, e> seg(N);
    for (auto i = 0; i < N; ++i) {
        seg.set(i, {A[i], A[i], i, i});
    }
    while (M--) {
        int l, r;
        cin >> l >> r;
        --l;
        auto x = seg.prod(l, r);
        auto i = x.min_pos;
        auto j = x.max_pos;
        swap(A[i], A[j]);
        seg.set(i, {A[i], A[i], i, i});
        seg.set(j, {A[j], A[j], j, j});
    }
    show(A);
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
