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
    i64 sum;
    array<int, 3> freq;
};

S op(S a, S b) {
    S c;
    c.sum = a.sum + b.sum;
    for (auto i = 0; i < 3; ++i) {
        for (auto j = 0; j < i; ++j) {
            c.sum += i64(a.freq[i]) * b.freq[j];
        }
    }
    for (auto i = 0; i < 3; ++i) {
        c.freq[i] = a.freq[i] + b.freq[i];
    }
    return c;
}

S e() { return {}; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    vector<S> v(N, e());
    for (auto i = 0; i < N; ++i) {
        v[i].sum = 0;
        v[i].freq[A[i]] = 1;
    }
    atcoder::segtree<S, op, e> seg(v);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            --i;
            S a{};
            a.freq[x] = 1;
            seg.set(i, a);
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << seg.prod(l, r).sum << "\n";
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
