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

void solve() {
    i64 N, M, K, X, Y;
    cin >> N >> M >> K >> X >> Y;
    vector<i64> A(N), B(M);
    read(A);
    read(B);
    ranges::sort(A);
    ranges::sort(B);
    vector<i64> pref = A;
    for (auto i = 0; i < N - 1; ++i) {
        pref[i + 1] += pref[i];
    }
    i64 cnt = 0;
    i64 ans = 0;
    auto F = [&] {
        auto x = X + K * Y;
        auto it = ranges::upper_bound(pref, x);
        ans = max(ans, cnt + (it - pref.begin()));
    };
    F();
    for (auto i = 0; i < M; ++i) {
        if (Y * K >= B[i]) {
            auto c = ceil_div(B[i], K);
            X += c * K - B[i];
            Y -= c;
            cnt++;
            F();
        } else {
            break;
        }
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
