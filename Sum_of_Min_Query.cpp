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

i64 op(i64 a, i64 b) { return a + b; }
i64 e() { return 0; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    vector<i64> A(N), B(N), C(N);
    read(A);
    read(B);
    for (auto i = 0; i < N; ++i) {
        C[i] = min(A[i], B[i]);
    }
    atcoder::segtree<i64, op, e> seg(C);
    while (Q--) {
        char c;
        int i, x;
        cin >> c >> i >> x;
        --i;
        if (c == 'A') {
            A[i] = x;
        } else {
            B[i] = x;
        }
        C[i] = min(A[i], B[i]);
        seg.set(i, C[i]);
        cout << seg.all_prod() << "\n";
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
