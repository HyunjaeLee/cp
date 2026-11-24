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

#define TC
void solve() {
    i64 N, K, X;
    cin >> N >> K >> X;
    vector<i64> A(N);
    read(A);
    auto pref = A;
    for (auto i = 0; i < N - 1; ++i) {
        pref[i + 1] += pref[i];
    }
    auto Pref = [&](i64 i) {
        assert(-1 <= i && i < N * K);
        if (i == -1)
            return 0LL;
        return pref[N - 1] * (i / N) + pref[i % N];
    };
    i64 ans = 0;
    for (i64 i = 0; i < N; ++i) {
        auto pred = [&](i64 r) { return Pref(r) - Pref(i - 1) < X; };
        auto v = views::iota(i, N * K);
        auto it = ranges::partition_point(v, pred);
        auto r = *it;
        auto s = r / N + 1;
        ans += max(0LL, K - s + 1);
    }
    cout << ans << "\n";
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
