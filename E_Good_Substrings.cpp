#include <atcoder/lazysegtree>
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
    i64 sum, len;
};

S op(S a, S b) { return {a.sum + b.sum, a.len + b.len}; }

S e() { return {0, 0}; }

using F = i64;

S mapping(F f, S x) { return {x.sum + x.len * f, x.len}; }

F composition(F f, F g) { return f + g; }

F id() { return 0; }

#define TC
void solve() {
    int N;
    string S_;
    cin >> N >> S_;
    vector<int> A(N);
    for (auto i = 0; i < N; ++i) {
        A[i] = S_[i] - '0';
    }
    vector<array<int, 10>> nxt(N);
    array<int, 10> ptr;
    ranges::fill(ptr, -1);
    for (auto i = N - 1; 0 <= i; --i) {
        ptr[A[i]] = i;
        nxt[i] = ptr;
    }
    atcoder::lazy_segtree<S, op, e, F, mapping, composition, id> seg(vector<S>(N + 10, {0, 1}));
    for (auto l = 0; l < N; ++l) {
        auto s = l;
        for (auto x : {2, 0, 2, 5}) {
            if (s != -1) {
                s = nxt[s][x];
            }
        }
        if (s == -1) {
            continue;
        }
        auto t = l;
        for (auto x : {2, 0, 2, 6}) {
            if (t != -1) {
                t = nxt[t][x];
            }
        }
        if (t == -1) {
            t = N - 1;
        } else {
            t--;
        }
        if (s > t) {
            continue;
        }
        seg.apply(l, l + 1, -(t - s + 1));
        seg.apply(s + 1, t + 2, +1);
    }
    vector<i64> ans(N);
    for (auto i = 0; i < N; ++i) {
        i64 a = i + 1;
        i64 b = N - i;
        ans[i] = seg.prod(0, i + 1).sum + a * b;
    }
    show(ans);
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
