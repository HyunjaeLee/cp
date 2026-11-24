#include <atcoder/modint>
#include <atcoder/segtree>
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

using S = array<Z, 6>;
S op(S a, S b) {
    S c;
    for (auto i = 0; i < 6; ++i) {
        c[i] = a[i] + b[i];
    }
    c[3] += a[0] * b[1];
    c[4] += a[1] * b[2];
    c[5] += a[3] * b[2] + a[0] * b[4];
    return c;
}
S e() { return {}; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    read(A);
    string s;
    cin >> s;
    auto f = [&](int p) {
        S a{};
        for (auto i = 0; i < 3; ++i) {
            if ("RGB"[i] == s[p]) {
                a[i] = A[p];
            }
        }
        return a;
    };
    vector<S> v(N);
    for (auto i = 0; i < N; ++i) {
        v[i] = f(i);
    }
    atcoder::segtree<S, op, e> seg(v);
    while (Q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int i, x;
            cin >> i >> x;
            --i;
            A[i] = x;
            seg.set(i, f(i));
        } else {
            int l, r;
            cin >> l >> r;
            --l;
            cout << seg.prod(l, r)[5].val() << "\n";
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
