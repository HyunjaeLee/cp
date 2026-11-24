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

int op(int a, int b) { return min(a, b); }

int e() { return inf; }

#include <atcoder/segtree>

void solve() {
    int Q;
    string S, T;
    cin >> Q >> S >> T;
    auto N = int(S.size());
    auto M = int(T.size());
    atcoder::segtree<int, op, e> seg(N);
    for (auto i = 0; i + M <= N; ++i) {
        auto ok = true;
        for (auto j = 0; j < M; ++j) {
            ok = ok && S[i + j] == T[j];
        }
        if (ok) {
            seg.set(i, i);
        }
    }
    while (Q--) {
        int L, R;
        cin >> L >> R;
        --L;
        auto p = seg.prod(L, R);
        auto ok = p + M <= R;
        cout << (ok ? "Yes\n" : "No\n");
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
