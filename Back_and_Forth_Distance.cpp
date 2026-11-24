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

#include <atcoder/segtree>

int op(int a, int b) { return min(a, b); }

int e() { return numeric_limits<int>::max() / 2; }

void solve() {
    int N, Q;
    cin >> N >> Q;
    atcoder::segtree<int, op, e> L(N), R(N);
    for (auto i = 1; i < N; ++i) {
        int x;
        cin >> x;
        L.set(i, x);
    }
    for (auto i = 0; i < N - 1; ++i) {
        int x;
        cin >> x;
        R.set(i, x);
    }
    while (Q--) {
        int s, t;
        cin >> s >> t;
        --s, --t;
        auto ans = 0;
        if (s < t) {
            auto a = R.get(s);
            auto b = L.get(s) + R.prod(0, s);
            ans = min(a, b);
        } else {
            auto a = L.get(s);
            auto b = R.get(s) + L.prod(s + 1, N);
            ans = min(a, b);
        }
        cout << ans << "\n";
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
